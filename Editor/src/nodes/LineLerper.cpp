

#include "nodes/LineLerper.h"

#include "imgui.h"

namespace Oedon::Editor
{

    bool LineLerper::View()
    {
        bool changed = false;

        ImGui::Text("Lerp Steps: ");
        ImGui::SameLine();
        changed = ImGui::DragInt("##lerpSteps", &_steps) || changed;

        return changed;
    }

    TravelStatus LineLerper::Process(TravelInfo &travelInfo)
    {
        if(inputPins[0]->connections.empty())
        {
            return TravelStatus::DependencyCannotBeMet;
        }

        auto& sourcePin = inputPins[0]->connections[0]->output;

        if(!sourcePin->cache.has_value())
        {
            travelInfo.dependencyRequired = sourcePin;
            return TravelStatus::NeedsDependency;
        }

        auto& outputPin = outputPins[0];
        outputPin->cache.reset();
        outputPin->cache.emplace(DataVariant{});
        outputPin->cache.value().SetType(DataVariantType::Points);
        auto& outputPoints = outputPin->cache.value().points;

        assert(sourcePin->cache->type == DataVariantType::Points);
        auto& sourcePoints = sourcePin->cache.value().points;

        size_t sourcePointSize = sourcePoints.size();
        if(sourcePointSize < 2)
        {
            return TravelStatus::Done;
        }

        for(int i = 0; i < sourcePointSize - 1; i++)
        {
            glm::vec3 part = sourcePoints[i + 1] - sourcePoints[i];
            part /= static_cast<float>(_steps);

            for(int j = 0 ; j < _steps + 1; j++)
            {
                outputPoints.emplace_back(sourcePoints[i] + (part * static_cast<float>(j)));
            }
        }

        return TravelStatus::Done;
    }

    LineLerper::LineLerper(BlueprintViewModel *vm) :
            NodeVM(vm, "Line Lerper"),
            _steps{10}
    {
        inputPins.emplace_back(vm->CreatePin("", {}, PinType::Input, PinCompat::Points));

        outputPins.emplace_back(vm->CreatePin("", {}, PinType::Output, PinCompat::Points));
    }
}
