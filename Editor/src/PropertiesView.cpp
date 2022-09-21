
#include "PropertiesView.h"

namespace Oedon::Editor
{

    PropertiesView::PropertiesView(EventDispatcher *eventDispatcher) :
    ListenFor(eventDispatcher),
    _eventDispatcher{eventDispatcher}
    {
    }

    void PropertiesView::OnEvent(NodeSelectionChangedEvent &event)
    {
        _selectedNode = event.node;
    }

    void PropertiesView::View()
    {
        if(_selectedNode)
        {
            if(_selectedNode->View())
            {
                NodePropertiesInvalidatedEvent event;
                event.node = _selectedNode;

                _eventDispatcher->Fire(event);
            }
        }
    }
}
