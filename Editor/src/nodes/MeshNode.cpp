
#include "nodes/MeshNode.h"

#include "BlueprintViewModel.h"
#include "Shapes.h"

#include "imgui.h"
#include "imgui_internal.h"

namespace Oedon::Editor
{
    static const char* NodeName = "Mesh Node";

    MeshNode::MeshNode(BlueprintViewModel *vm) :
            NodeVM(vm, NodeName),
            _option{0},
            _sphereV{10},
            _sphereH{10},
            _cubeSize{0.5f},
            _sphereR{1.0f}
    {
        auto outputPin = vm->CreatePin("", {}, PinType::Output, PinCompat::Mesh);
        outputPins.push_back(outputPin);
    }

    bool MeshNode::View()
    {
        bool changed = false;

        const char* options[] = {
                "Cube",
                "Sphere"
        };

        ImGui::Text("Mesh: ");
        changed = ImGui::Combo("##meshNodeMeshType", &_option, options, sizeof(options) / sizeof(options[0]));

        if(_option == 0)
        {
            ImGui::Text("Cube: ");
            ImGui::SameLine();
            changed = ImGui::DragFloat("##meshNodeCubeSize", &_cubeSize, 0.25f, 0.5f, MAXFLOAT, "%.3f", ImGuiSliderFlags_AlwaysClamp) || changed;
        }
        else if(_option == 1)
        {
            ImGui::Text("SphereV: ");
            ImGui::SameLine();
            changed = ImGui::DragInt("##meshNodeSphereV", &_sphereV, 1.0f, 3, INT_MAX, "%d", ImGuiSliderFlags_AlwaysClamp) || changed;

            ImGui::Text("SphereH: ");
            ImGui::SameLine();
            changed = ImGui::DragInt("##meshNodeSphereH", &_sphereH, 1.0f, 3, INT_MAX, "%d", ImGuiSliderFlags_AlwaysClamp) || changed;

            ImGui::Text("SphereR: ");
            ImGui::SameLine();
            changed = ImGui::DragFloat("##meshNodeSphereHR", &_sphereR, 0.5f, 0.5f, MAXFLOAT, "%.3f", ImGuiSliderFlags_AlwaysClamp) || changed;
        }

        return changed;
    }

    TravelStatus MeshNode::Process(TravelInfo &travelInfo)
    {
        outputPins[0]->cache.emplace(DataVariant{});
        auto& data = outputPins[0]->cache.value();
        data.SetType(DataVariantType::Mesh);
        switch(_option)
        {
            case 1:
                data.mesh = Sphere(_sphereH, _sphereV, _sphereR);
                break;
            default:
                data.mesh = Cube(_cubeSize);
        }
        return TravelStatus::Done;
    }
}
