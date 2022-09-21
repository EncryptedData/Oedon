#pragma once

#include "BlueprintViewModel.h"

namespace Oedon::Editor
{
    class LineLerper : public NodeVM
    {
    public:
        explicit LineLerper(BlueprintViewModel* vm);

        bool View() override;

        TravelStatus Process(TravelInfo &travelInfo) override;

    private:
        int _steps;
    };
}
