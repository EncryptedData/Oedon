//
// Created by Russell Johnson on 9/6/22.
//
#pragma once

#include "NodeFactory.h"
#include "EventDispatcher.h"
#include "Events.h"
#include "DataVariant.h"

#include <vector>
#include <memory>
#include <string>
#include <string_view>
#include <functional>
#include <optional>

namespace ax::NodeEditor
{
    struct EditorContext;
}

namespace Oedon::Editor
{
    enum class PinType
    {
        Input,
        Output,
    };

    enum class PinCompat
    {
        Mesh,
        Points,
        Texture,
    };

    enum IconType
    {
        Flow,
        Circle,
        Square,
        Grid,
        RoundSquare,
        Diamond
    };

    enum class TravelStatus
    {
        Done,
        NeedsDependency,
        DependencyCannotBeMet,
    };

    using ItemId = std::uint64_t;

    struct PinVM;
    struct NodeVM;
    struct ConnectionVM;
    struct BluerprintViewModel;

    struct TravelInfo
    {
        std::shared_ptr<PinVM> dependencyRequired;
        std::shared_ptr<PinVM> currentPin;
    };

    struct PinVM
    {
        ItemId id;
        PinType type;
        PinCompat compat;
        std::string label;
        std::shared_ptr<NodeVM> node;
        std::vector<std::shared_ptr<ConnectionVM>> connections;
        std::optional<DataVariant> cache;
    };

    struct NodeVM
    {
        // Makes std::make_shared work
        typedef std::shared_ptr<NodeVM> Ptr;

        ItemId id;
        std::string name;
        std::vector<std::shared_ptr<PinVM>> inputPins;
        std::vector<std::shared_ptr<PinVM>> outputPins;

        NodeVM(BlueprintViewModel* vm, std::string_view name);

        virtual ~NodeVM() = default;

        virtual bool View() = 0;

        virtual TravelStatus Process(TravelInfo& travelInfo) = 0;

        virtual void OnPinAttached(std::shared_ptr<PinVM>& pin, BluerprintViewModel* vm);

        virtual void OnPinDisconnected(std::shared_ptr<PinVM>& pin, BluerprintViewModel* vm);

        virtual void OnSelected(BluerprintViewModel* vm);
    };

    struct ConnectionVM
    {
        ItemId id;
        PinCompat compat;
        std::shared_ptr<PinVM> input;
        std::shared_ptr<PinVM> output;
    };

    struct BlueprintViewModel : ListenFor<NodePropertiesInvalidatedEvent>
    {
        explicit BlueprintViewModel(EventDispatcher* dispatcher);

        EventDispatcher* eventDispatcher;
        ItemId uniqueId;
        std::vector<ItemId> unusedIds;
        std::vector<std::shared_ptr<NodeVM>> nodes;
        std::vector<std::shared_ptr<ConnectionVM>> connections;
        ax::NodeEditor::EditorContext* editorContext;
        NodeFactory factory;
        std::optional<ItemId> selectedNode;

        ItemId GetNextId();
        void ReturnId(ItemId id);

        std::shared_ptr<PinVM> CreatePin(std::string_view label, const std::shared_ptr<NodeVM>& node, PinType pinType, PinCompat pinCompat);
        std::shared_ptr<ConnectionVM> CreateConnection(const std::shared_ptr<PinVM>& inputPin, const std::shared_ptr<PinVM>& outputPin);
        void DestroyNode(const std::shared_ptr<NodeVM>& node);
        void DestroyPin(const std::shared_ptr<PinVM>& pin);
        void DestroyConnection(const std::shared_ptr<ConnectionVM>& connection);
        void BreakPinConnections(const std::shared_ptr<PinVM>& pin);

        std::shared_ptr<PinVM> FindPinWithId(ItemId pinId);
        std::shared_ptr<ConnectionVM> FindConnectionWithId(ItemId connectionId);
        std::shared_ptr<NodeVM> FindNodeWithId(ItemId nodeId);

        void ProcessNodes(const std::shared_ptr<NodeVM>& node);
        void InvalidateNodes(const std::shared_ptr<NodeVM>& node);

        template<typename NodeType>
        std::shared_ptr<NodeVM> BuildNode()
        {
            auto node = factory.Build<NodeType>(this);

            for(auto& pin : node->inputPins)
            {
                pin->node = node;
            }

            for(auto& pin : node->outputPins)
            {
                pin->node = node;
            }

            nodes.push_back(node);

            return node;
        }

        void OnEvent(NodePropertiesInvalidatedEvent &event) override;
    };
}