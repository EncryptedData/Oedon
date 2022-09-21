
#include "nodes/CubeNode.h"

#include "BlueprintViewModel.h"
#include "Shapes.h"

#include "imgui.h"
#include "imgui_internal.h"

namespace Oedon::Editor
{
    static const char* NodeName = "Cube";

    CubeNode::CubeNode(BlueprintViewModel *vm) :
            NodeVM(vm, NodeName)
    {
        auto outputPin = vm->CreatePin("", {}, PinType::Output, PinCompat::Mesh);
        outputPins.push_back(outputPin);
    }

    bool CubeNode::View()
    {
        return false;
    }

    TravelStatus CubeNode::Process(TravelInfo &travelInfo)
    {
        outputPins[0]->cache.emplace(DataVariant{});
        auto& data = outputPins[0]->cache.value();
        data.SetType(DataVariantType::Mesh);
        data.mesh = Cube();
        return TravelStatus::Done;
    }
}
