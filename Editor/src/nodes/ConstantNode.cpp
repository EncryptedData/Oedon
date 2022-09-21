
#include "nodes/ConstantNode.h"

namespace Oedon::Editor
{

    bool ConstantNode::View()
    {
        return false;
    }

    TravelStatus ConstantNode::Process(TravelInfo &travelInfo)
    {
        auto& outputPin = outputPins[0];

        if(!outputPin->cache.has_value())
        {
            outputPin->cache.emplace(DataVariant{});
            auto& cache = outputPin->cache.value();
            cache.SetType(DataVariantType::Points);
            cache.points.emplace_back(glm::vec3(-10.0, 0.0f, -10.0f));
            cache.points.emplace_back(glm::vec3(10.0, 0.0f, 10.0f));
        }
        return TravelStatus::Done;
    }

    ConstantNode::ConstantNode(BlueprintViewModel *vm) :
            NodeVM(vm, "Constant Value")
    {
        outputPins.push_back(vm->CreatePin("", {}, PinType::Output, PinCompat::Points));
    }
}
