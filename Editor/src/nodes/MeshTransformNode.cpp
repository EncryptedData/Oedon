
#include "nodes/MeshTransformNode.h"
#include "BlueprintViewModel.h"

#include <iostream>
#include <string_view>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

namespace Oedon::Editor
{
    static const char* NodeName = "Mesh Transform";

    static void PrintMat(const glm::mat4& mat, std::string_view name)
    {
        std::cout << std::endl <<  name << std::endl;
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                std::cout << mat[j][i] << "   ";
            }

            std::cout << std::endl;
        }
    }

    MeshTransformNode::MeshTransformNode(BlueprintViewModel* vm) :
        NodeVM(vm, NodeName),
        _scale(1.0f, 1.0f, 1.0f),
        _translation(0.0f, 0.0f, 0.0f),
        _rotAxis(0.0f, 1.0f, 0.0f),
        _rotAngle(0.0f)
    {
        inputPins.emplace_back(vm->CreatePin("Mesh", {}, PinType::Input, PinCompat::Mesh));

        auto outputPin = vm->CreatePin("", {}, PinType::Output, PinCompat::Mesh);
        outputPins.push_back(outputPin);
    }

    bool MeshTransformNode::View()
    {
        bool valueChanged = false;

        ImGui::Text("Scale (XYZ):");
        ImGui::SameLine();
        valueChanged = ImGui::DragFloat3("##transformScale", glm::value_ptr(_scale), 0.1f) || valueChanged;

        ImGui::Text("Translation (XYZ):");
        ImGui::SameLine();
        valueChanged = ImGui::DragFloat3("##transformTranslation", glm::value_ptr(_translation), 0.1f) || valueChanged;

        ImGui::Text("Rotation Axis (XYZ):");
        ImGui::SameLine();
        valueChanged = ImGui::DragFloat3("##transformRotAxis", glm::value_ptr(_rotAxis), 0.1f) || valueChanged;

        ImGui::Text("Rotation Angle:");
        ImGui::SameLine();
        valueChanged = ImGui::DragFloat("##transformRotAngle", &_rotAngle, 0.1f) || valueChanged;

        return valueChanged;
    }

    TravelStatus MeshTransformNode::Process(TravelInfo &travelInfo)
    {
        assert(!travelInfo.currentPin->node->inputPins.empty());
        auto& inputPin = travelInfo.currentPin->node->inputPins[0];
        if(inputPin->connections.empty())
        {
            return TravelStatus::DependencyCannotBeMet;
        }

        auto& otherNodePin = inputPin->connections[0]->output;

        if(!otherNodePin->cache.has_value())
        {
            travelInfo.dependencyRequired = otherNodePin;
            return TravelStatus::NeedsDependency;
        }


        travelInfo.currentPin->cache.emplace(DataVariant{});
        auto& outputData = travelInfo.currentPin->cache.value();
        outputData.SetType(DataVariantType::Mesh);

        auto& inputData = otherNodePin->cache.value();
        assert(inputData.type == DataVariantType::Mesh);

        glm::mat4 transformation(1.0f);
        transformation = glm::translate(transformation, _translation);
        transformation = glm::rotate(transformation, _rotAngle, _rotAxis);
        transformation = glm::scale(transformation, _scale);
        glm::mat4 inverseTransform = glm::transpose(glm::inverse(transformation));

        PrintMat(transformation, "Transform");
        PrintMat(inverseTransform, "Inverse Transform");

        outputData.mesh = inputData.mesh;

        for(auto& vert : outputData.mesh.verticies)
        {
            glm::vec4 position = transformation * glm::vec4(vert, 1.0f);
            float w = position.w;
            position /= w;

            vert = glm::vec3(position);
        }

        for(auto& normal : outputData.mesh.normals)
        {
            normal = glm::normalize(glm::vec3(glm::vec4(normal, 0.0f) * inverseTransform));
        }

        return TravelStatus::Done;
    }
}

