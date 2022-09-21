//
// Created by Russell Johnson on 9/6/22.
//

#include "BlueprintViewModel.h"

#include <imgui_node_editor.h>
namespace ed = ax::NodeEditor;

namespace Oedon::Editor
{


    BlueprintViewModel::BlueprintViewModel(EventDispatcher* dispatcher) :
        ListenFor<NodePropertiesInvalidatedEvent>(dispatcher),
        eventDispatcher{dispatcher},
        uniqueId{1}
    {
        ed::Config config;
        editorContext = ed::CreateEditor(&config);
    }

    std::shared_ptr<PinVM> BlueprintViewModel::CreatePin(std::string_view label, const std::shared_ptr<NodeVM>& node, PinType pinType, PinCompat pinCompat)
    {
        auto pin = std::make_shared<PinVM>();
        pin->node = node;
        pin->type = pinType;
        pin->compat = pinCompat;
        pin->label = label;
        pin->id = GetNextId();
        return pin;
    }

    std::shared_ptr<ConnectionVM> BlueprintViewModel::CreateConnection(const std::shared_ptr<PinVM> &inputPin,
                                                                       const std::shared_ptr<PinVM> &outputPin)
    {
        auto connection = std::make_shared<ConnectionVM>();
        connection->id = GetNextId();
        connection->input = inputPin;
        connection->output = outputPin;

        connection->compat = inputPin->compat;

        connections.push_back(connection);
        return connection;
    }

    void BlueprintViewModel::DestroyConnection(const std::shared_ptr<ConnectionVM> &connection)
    {
        if(connection->output)
        {
            connection->output->connections.erase(std::remove(connection->output->connections.begin(), connection->output->connections.end(), connection));
        }

        if(connection->input)
        {
            connection->input->connections.clear();
        }

        connections.erase(std::find(connections.begin(), connections.end(), connection));

        ReturnId(connection->id);
    }

    ItemId BlueprintViewModel::GetNextId()
    {
        if(unusedIds.empty())
        {
            return uniqueId++;
        }

        ItemId id = unusedIds.back();
        unusedIds.pop_back();

        return id;
    }

    void BlueprintViewModel::ReturnId(ItemId id)
    {
        unusedIds.push_back(id);
    }

    void BlueprintViewModel::BreakPinConnections(const std::shared_ptr<PinVM> &pin)
    {
        if(!pin->connections.empty())
        {
            for(auto connection : pin->connections)
            {
                DestroyConnection(connection);
            }
        }
    }

    void BlueprintViewModel::DestroyNode(const std::shared_ptr<NodeVM> &node)
    {
        InvalidateNodes(node);

        for(auto pin : node->inputPins)
        {
            BreakPinConnections(pin);
            DestroyPin(pin);
        }

        for(auto pin : node->outputPins)
        {
            BreakPinConnections(pin);
            DestroyPin(pin);
        }

        nodes.erase(std::find(nodes.begin(), nodes.end(), node));

        ReturnId(node->id);
    }

    void BlueprintViewModel::DestroyPin(const std::shared_ptr<PinVM> &pin)
    {
        ReturnId(pin->id);
        pin->node.reset();
    }

    std::shared_ptr<PinVM> BlueprintViewModel::FindPinWithId(ItemId pinId)
    {
        for(const auto& node : nodes)
        {
            for(const auto& pin : node->inputPins)
            {
                if(pin->id == pinId)
                {
                    return pin;
                }
            }

            for(const auto& pin : node->outputPins)
            {
                if(pin->id == pinId)
                {
                    return pin;
                }
            }
        }

        return {};
    }

    std::shared_ptr<ConnectionVM> BlueprintViewModel::FindConnectionWithId(ItemId connectionId)
    {
        for(const auto& connection : connections)
        {
            if(connection->id == connectionId)
            {
                return connection;
            }
        }

        return {};
    }

    std::shared_ptr<NodeVM> BlueprintViewModel::FindNodeWithId(ItemId nodeId)
    {
        for(const auto& node : nodes)
        {
            if(node->id == nodeId)
            {
                return node;
            }
        }

        return {};
    }

    void BlueprintViewModel::ProcessNodes(const std::shared_ptr<NodeVM>& node)
    {
        // For right now assume first output pin is default view
        if(node->outputPins.empty())
        {
            return;
        }

        std::vector<std::shared_ptr<PinVM>> tree;
        tree.push_back(node->outputPins[0]);

        while(!tree.empty())
        {
            auto pin = tree.back();
            tree.pop_back();

            if(pin->cache.has_value())
            {
                continue;
            }

            auto& node = pin->node;

            TravelInfo info{};
            info.currentPin = pin;
            TravelStatus result = node->Process(info);

            if(result == TravelStatus::NeedsDependency)
            {
                tree.push_back(pin);
                tree.push_back(info.dependencyRequired);
            }
            else if(result == TravelStatus::DependencyCannotBeMet)
            {
                return;
            }
            else
            {
                assert(pin->cache.has_value());
            }
        }
    }

    void BlueprintViewModel::OnEvent(NodePropertiesInvalidatedEvent &event)
    {
        if(event.node)
        {
            InvalidateNodes(event.node);

            if(selectedNode && selectedNode == event.node->id)
            {
                ProcessNodes(event.node);

                RefreshSceneViewEvent refreshEvent;
                refreshEvent.node = event.node;

                eventDispatcher->Fire(refreshEvent);
            }
        }
    }

    void BlueprintViewModel::InvalidateNodes(const std::shared_ptr<NodeVM> &node)
    {
        if(node->outputPins.empty())
        {
            return;
        }

        std::vector<std::shared_ptr<PinVM>> tree;
        tree.insert(tree.end(), node->outputPins.begin(), node->outputPins.end());

        while(!tree.empty())
        {
            auto pin = tree.back();
            tree.pop_back();

            if(!pin->cache.has_value())
            {
                continue;
            }

            pin->cache.reset();

            if(!pin->connections.empty())
            {
                auto& pinNode = pin->connections[0]->input->node;
                tree.insert(tree.end(), pinNode->outputPins.begin(), pinNode->outputPins.end());
            }
        }
    }

    NodeVM::NodeVM(BlueprintViewModel* vm, std::string_view displayName) :
        id(vm->GetNextId()),
        name(displayName)
    {
    }

    void NodeVM::OnPinAttached(std::shared_ptr<PinVM> &pin, BluerprintViewModel *vm)
    {
    }

    void NodeVM::OnPinDisconnected(std::shared_ptr<PinVM> &pin, BluerprintViewModel *vm)
    {
    }

    void NodeVM::OnSelected(BluerprintViewModel *vm)
    {
    }


}
