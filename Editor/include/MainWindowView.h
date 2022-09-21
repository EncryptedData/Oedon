
#include "BlueprintView.h"
#include "SceneView.h"
#include "PropertiesView.h"

namespace Oedon::Editor
{
    struct MainWindowViewModel;

    class MainWindowView
    {
    public:

        explicit MainWindowView(EventDispatcher* dispatcher);

        void View(MainWindowViewModel* vm);

    private:
        BlueprintView _blueprintView;
        SceneView _sceneView;
        PropertiesView _propertiesView;
        bool _firstFrame;
    };
}
