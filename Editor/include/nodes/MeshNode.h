#pragma once

#include "BlueprintViewModel.h"

namespace Oedon::Editor
{
    class MeshNode : public NodeVM
    {
    public:
        explicit MeshNode(BlueprintViewModel* vm);

        bool View() override;

        TravelStatus Process(TravelInfo &travelInfo) override;

    private:
        int _option;
        int _sphereV;
        int _sphereH;
        float _cubeSize;
        float _sphereR;
    };
}

