#pragma once

#include "BlueprintViewModel.h"
#include <glm/vec3.hpp>

namespace Oedon::Editor
{
    class MeshTransformNode :
            public NodeVM
    {
    public:

        explicit MeshTransformNode(BlueprintViewModel* vm);

        bool View() override;

        TravelStatus Process(TravelInfo &travelInfo) override;

    private:

        glm::vec3 _scale;
        glm::vec3 _translation;
        glm::vec3 _rotAxis;
        float _rotAngle;
    };
}
