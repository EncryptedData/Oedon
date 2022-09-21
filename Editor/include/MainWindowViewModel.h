#pragma once

#include "BlueprintViewModel.h"
#include "SceneViewModel.h"

namespace Oedon::Editor
{
    struct MainWindowViewModel
    {
        explicit MainWindowViewModel();

        EventDispatcher dispatcher;
        BlueprintViewModel blueprintViewModel;
        SceneViewModel sceneViewModel;
    };


}