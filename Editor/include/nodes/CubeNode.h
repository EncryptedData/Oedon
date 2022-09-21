#pragma once

#include "BlueprintViewModel.h"

namespace Oedon::Editor
{
    class CubeNode : public NodeVM
    {
    public:
        explicit CubeNode(BlueprintViewModel* vm);

        bool View() override;

        TravelStatus Process(TravelInfo &travelInfo) override;
    };
}

