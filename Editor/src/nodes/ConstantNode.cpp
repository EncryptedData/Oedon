
#include "nodes/ConstantNode.h"
#include "Shapes.h"

#include "imgui.h"

namespace Oedon::Editor
{

    bool ConstantNode::View()
    {
        bool changed = false;

        ImGui::Text("Sphere H:");
        ImGui::SameLine();
        changed = ImGui::DragInt("##constantNodeSphereH", &_sphereH, 1, 1);

        ImGui::Text("Sphere V:");
        ImGui::SameLine();
        changed = ImGui::DragInt("##constantNodeSphereV", &_sphereV, 1, 1) || changed;

        ImGui::Text("Sphere R:");
        ImGui::SameLine();
        changed = ImGui::DragFloat("##constantNodeSphereR", &_sphereR, 1.0f, 1.0f) || changed;

        return changed;
    }

    TravelStatus ConstantNode::Process(TravelInfo &travelInfo)
    {
        auto& outputPin = outputPins[0];

        outputPin->cache.emplace(DataVariant{});
        auto& cache = outputPin->cache.value();
        cache.SetType(DataVariantType::Points);
        //cache.points.emplace_back(glm::vec3(-10.0, 0.0f, -10.0f));
        //cache.points.emplace_back(glm::vec3(10.0, 0.0f, 10.0f));

        auto m = Sphere(_sphereH, _sphereV, _sphereR);

        for(const auto& [_, vert] :  m.verticies())
        {
            cache.points.emplace_back(vert.position);
        }
        return TravelStatus::Done;
    }

    ConstantNode::ConstantNode(BlueprintViewModel *vm) :
            NodeVM(vm, "Constant Value"),
            _sphereH{10},
            _sphereV{10},
            _sphereR{1.0f}
    {
        outputPins.push_back(vm->CreatePin("", {}, PinType::Output, PinCompat::Points));
    }
}
