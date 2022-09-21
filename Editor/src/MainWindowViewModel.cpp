
#include "MainWindowViewModel.h"

namespace Oedon::Editor
{
    MainWindowViewModel::MainWindowViewModel() :
            dispatcher(),
            blueprintViewModel(&dispatcher),
            sceneViewModel(&dispatcher)
    {
    }
}
