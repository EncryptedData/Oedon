#pragma once

#include "BlueprintViewModel.h"

namespace Oedon::Editor
{
    class ConstantNode : public NodeVM
    {
    public:
        explicit ConstantNode(BlueprintViewModel* vm);

        bool View() override;

        TravelStatus Process(TravelInfo &travelInfo) override;


    private:
        int _sphereH;
        int _sphereV;
        float _sphereR;
    };
}
