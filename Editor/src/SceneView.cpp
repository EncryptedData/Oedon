
#include "SceneView.h"
#include "SceneViewModel.h"

#include <imgui.h>
#include <imgui_canvas.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Oedon::Editor
{
    static void RotateVec(glm::vec3& dir, const glm::vec3& axis, float amount)
    {
        auto rot = glm::rotate(glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::radians(amount), axis);
        dir = dir * rot;
    }

    void SceneView::Render(SceneViewModel *vm)
    {
        const float ScrollMoveScale = 5.0f;
        const float KeyboardMoveScale = 0.5f;
        const float KeyboardLookScale = 1.0f;
        const float MouseMoveScale = 1.0f;
        const glm::vec3 globalUp(0.0f, 1.0f, 0.0f);
        static float fov = 25.0f;

        if(ImGui::Button("Reset Camera"))
        {
            vm->camera_pos = glm::vec3(25.0f, 25.0f, 25.0f);
            vm->camera_dir = glm::normalize(-vm->camera_pos);
        }

        ImGui::BeginChild("SceneView3D");
        ImVec2 wsize = ImGui::GetWindowSize();

        vm->framebuffer->Bind();
        vm->framebuffer->Resize(wsize.x, wsize.y);
        vm->framebuffer->Clear();

        if(vm->mesh)
        {
            auto& io = ImGui::GetIO();

            if(ImGui::IsWindowHovered())
            {

                //vm->camera_dist;
                vm->camera_pos += vm->camera_dir * io.MouseWheel * ScrollMoveScale;
            }

            if(ImGui::IsWindowFocused())
            {
                glm::vec3 cameraOrth = glm::normalize(glm::cross(vm->camera_dir, globalUp));

                if(io.KeysDown[ImGuiKey_W])
                {
                    vm->camera_pos += vm->camera_dir * KeyboardMoveScale;
                }

                if(io.KeysDown[ImGuiKey_S])
                {
                    vm->camera_pos -= vm->camera_dir * KeyboardMoveScale;
                }

                if(io.KeysDown[ImGuiKey_A])
                {
                    vm->camera_pos -= cameraOrth * KeyboardMoveScale;
                }

                if(io.KeysDown[ImGuiKey_D])
                {
                    vm->camera_pos += cameraOrth * KeyboardMoveScale;
                }

                if(io.KeysDown[ImGuiKey_F])
                {
                    vm->camera_dir = glm::normalize(-vm->camera_pos);
                }

                if(io.KeysDown[ImGuiKey_LeftArrow])
                {
                    RotateVec(vm->camera_dir, globalUp, KeyboardLookScale);
                }

                if(io.KeysDown[ImGuiKey_RightArrow])
                {
                    RotateVec(vm->camera_dir, globalUp, -KeyboardLookScale);
                }

                if(io.KeysDown[ImGuiKey_UpArrow])
                {
                    RotateVec(vm->camera_dir, cameraOrth, -KeyboardLookScale);
                }

                if(io.KeysDown[ImGuiKey_DownArrow])
                {
                    RotateVec(vm->camera_dir, cameraOrth, KeyboardLookScale);
                }


                static ImVec2 lastMousePos(0.0f, 0.0f);
                if(ImGui::IsMouseClicked(ImGuiMouseButton_Left, true))
                {
                    ImVec2 mousePos = ImGui::GetMousePos();

                    ImVec2 mouseDelta = mousePos;
                    mouseDelta.x -= lastMousePos.x;
                    mouseDelta.y -= lastMousePos.y;

                    float testX = 0.8f;
                    float testY = 0.25;

                    RotateVec(vm->camera_dir, globalUp, -mouseDelta.x * testX);
                    RotateVec(vm->camera_dir, cameraOrth, -mouseDelta.y * testY);

                    lastMousePos = mousePos;
                }
                else
                {
                    lastMousePos = ImGui::GetMousePos();
                }
            }

            // Calculate transforms
            //glm::mat4 meshToWorld = glm::mat4(1.0f);
            glm::mat4 worldToCamera = glm::lookAt(vm->camera_pos, vm->camera_pos + vm->camera_dir, glm::vec3(0.0f, 1.0f, 0.0f));
            //glm::mat4 worldToCamera = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
            //glm::mat4 cameraToNdc = glm::perspective(glm::radians(90.0f), wsize.x / wsize.y, 0.1f, 500.0f);
            glm::mat4 cameraToNdc = glm::perspective(glm::radians(fov), wsize.x / wsize.y, 0.1f, 500.0f);

            glm::mat4 worldToNdc = cameraToNdc * worldToCamera;

            // Set the shader uniforms
            vm->currentShader->Bind();
            //vm->shader->Set("meshToWorld", meshToWorld);
            //vm->shader->Set("worldToNdc", worldToNdc);
            //vm->shader->Set("mesh", meshToWorld);
            //vm->shader->Set("camera", worldToCamera);
            //vm->shader->Set("proj", cameraToNdc);
            vm->currentShader->Set("proj", worldToNdc);
            vm->currentShader->Set("debugColor", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

            vm->mesh->Bind();
            vm->mesh->Draw();
            vm->mesh->Unbind();

            vm->currentShader->Unbind();
        }

        vm->framebuffer->Unbind();

        unsigned texture = vm->framebuffer->GetColorTexture();

        ImGui::Image((ImTextureID)texture, wsize, ImVec2(0, 1), ImVec2(1, 0));
        ImGui::EndChild();
    }


}
