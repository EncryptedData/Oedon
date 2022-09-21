#pragma once

#include "EventDispatcher.h"
#include "Events.h"
#include "BlueprintViewModel.h"

#include <optional>

namespace Oedon::Editor
{
    class PropertiesView : ListenFor<NodeSelectionChangedEvent>
    {
    public:
        explicit PropertiesView(EventDispatcher* eventDispatcher);

        void View();

    private:
        void OnEvent(NodeSelectionChangedEvent &event) override;
        EventDispatcher* _eventDispatcher;
        std::shared_ptr<NodeVM> _selectedNode;
    };
}
