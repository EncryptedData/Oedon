//
// Created by Russell Johnson on 9/5/22.
//

#include "MainWindowView.h"
#include "MainWindowViewModel.h"

#include <imgui.h>
#include <imgui_internal.h>

namespace Oedon::Editor
{
    static const char * LABEL_MAIN_DOCK_NODE = "MAIN_DOCKSPACE";
    static const char * LABEL_DOCK_VIEW = "3D View##DOCK_VIEW";
    static const char * LABEL_DOCK_BLUEPRINT = "Blueprint##DOCK_BLUEPRINT";
    static const char * LABEL_DOCK_PROPERTIES = "Properties##DOCK_PROPERTIES";

    static const char* LABELS_DOCKS[] = {
            "DOCK_UP",
            "DOCK_RIGHT",
            "DOCK_LEFT",
            "DOCK_DOWN",
            "DOCK_DOWN_RIGHT",
            "DOCK_MAIN"
    };

    void Editor::MainWindowView::View(MainWindowViewModel* vm)
    {
        ImGuiViewport* mainViewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(mainViewport->Pos);
        ImGui::SetNextWindowSize(mainViewport->Size);
        ImGui::SetNextWindowViewport(mainViewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking |
                ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;



        ImGui::Begin(LABEL_MAIN_DOCK_NODE, nullptr, windowFlags);
        ImGui::PopStyleVar(2);

        if(_firstFrame)
        {
            _firstFrame = false;

            ImGuiID mainNodeId = ImGui::GetID(LABEL_MAIN_DOCK_NODE);
            ImGui::DockBuilderRemoveNode(mainNodeId);
            ImGui::DockBuilderAddNode(mainNodeId, ImGuiDockNodeFlags_None);

            ImGui::DockBuilderSetNodePos(mainNodeId, mainViewport->Pos);
            ImGui::DockBuilderSetNodeSize(mainNodeId, mainViewport->Size);

            ImGuiID dockMainId = mainNodeId;
            //ImGuiID dockUpId = ImGui::DockBuilderSplitNode(dockMainId, ImGuiDir_Up, 0.05f, nullptr, &dockMainId);
            ImGuiID dockRightId = ImGui::DockBuilderSplitNode(dockMainId, ImGuiDir_Right, 0.2f, nullptr, &dockMainId);
            //ImGuiID dockLeftId = ImGui::DockBuilderSplitNode(dockMainId, ImGuiDir_Left, 0.2f, nullptr, &dockMainId);
            ImGuiID dockDownId = ImGui::DockBuilderSplitNode(dockMainId, ImGuiDir_Down,  0.5f, nullptr, &dockMainId);
            //ImGuiID dockDownRightId = ImGui::DockBuilderSplitNode(dockDownId, ImGuiDir_Right, 0.6f, nullptr, &dockDownId);

            ImGui::DockBuilderDockWindow(LABEL_DOCK_PROPERTIES, dockRightId);
            ImGui::DockBuilderDockWindow(LABEL_DOCK_BLUEPRINT, dockDownId);
            ImGui::DockBuilderDockWindow(LABEL_DOCK_VIEW, dockMainId);

            ImGuiDockNode* mainNode = ImGui::DockBuilderGetNode(dockMainId);
            while(mainNode->ParentNode != nullptr)
            {
                mainNode = mainNode->ParentNode;
            }

            mainNode->LocalFlagsInWindows |= ImGuiWindowFlags_NoMove;
            mainNode->UpdateMergedFlags();

            ImGui::DockBuilderFinish(dockMainId);

            vm->sceneViewModel.Init();
        }

        ImGuiID dockspaceId = ImGui::GetID(LABEL_MAIN_DOCK_NODE);
        ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

        ImGui::BeginMenuBar();
        if(ImGui::BeginMenu("File"))
        {
            if(ImGui::MenuItem("Open"))
            {
            }

            if(ImGui::MenuItem("Save"))
            {
            }

            if(ImGui::MenuItem("Exit"))
            {
            }

            ImGui::EndMenu();
        }


        if(ImGui::BeginMenu("Help"))
        {
            ImGui::MenuItem("No go away...");
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();



        ImGui::End();

        ImGui::Begin(LABEL_DOCK_VIEW);
        _sceneView.Render(&vm->sceneViewModel);
        ImGui::End();

        ImGui::Begin(LABEL_DOCK_BLUEPRINT);
        _blueprintView.View(&vm->blueprintViewModel);
        ImGui::End();

        ImGui::Begin(LABEL_DOCK_PROPERTIES);
        ImGui::Text("Property Area");
        ImGui::Text("FPS: %f", ImGui::GetIO().Framerate);

        _propertiesView.View();
        ImGui::End();
    }

    MainWindowView::MainWindowView(EventDispatcher* dispatcher) :
        _firstFrame{true},
        _propertiesView{dispatcher},
        _sceneView()
    {

    }
}
