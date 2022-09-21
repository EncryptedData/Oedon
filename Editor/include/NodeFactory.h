#pragma once

#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include <type_traits>

namespace Oedon::Editor
{
    struct BlueprintViewModel;
    struct NodeVM;
    struct PinVM;

    class NodeFactory
    {
    public:

        explicit NodeFactory();

        ~NodeFactory();

        void RegisterNodes();

        template<typename NodeType>
        void Register()
        {
            static_assert(std::is_base_of<NodeVM, NodeType>::value, "You cannot register non nodes!");

            std::type_index index(typeid(NodeType));

            //_nodes[index] = new NodeType;
        }

        template<typename NodeType>
        std::shared_ptr<NodeVM> Build(struct BlueprintViewModel* vm)
        {
            static_assert(std::is_base_of<NodeVM, NodeType>::value, "You cannot register non nodes!");

            auto node = std::shared_ptr<NodeVM>(new NodeType(vm));

            return node;
        }

    private:
    };
}
