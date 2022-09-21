//
// Created by Russell Johnson on 9/7/22.
//

#pragma once

#include "EventDispatcher.h"
#include "Events.h"

namespace Oedon::Editor
{
    struct SceneViewModel;

    class SceneView
    {
    public:

        void Render(SceneViewModel* vm);
    };
}
