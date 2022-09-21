#pragma once

#include <memory>

namespace Oedon::Editor
{
    struct NodeVM;

    struct NodeSelectionChangedEvent
    {
        std::shared_ptr<NodeVM> node;
    };

    struct NodePropertiesInvalidatedEvent
    {
        std::shared_ptr<NodeVM> node;
    };

    struct RefreshSceneViewEvent
    {
        std::shared_ptr<NodeVM> node;
    };
}
