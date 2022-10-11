
#include "NodeFactory.h"

// Nodes
#include "nodes/MeshNode.h"
#include "nodes/MeshTransformNode.h"

namespace Oedon::Editor
{

    NodeFactory::NodeFactory()
        //_nodes{}
    {
        RegisterNodes();
    }

    NodeFactory::~NodeFactory()
    {
        //for(auto& node : _nodes)
        //{
        //    delete node.second;
        //}
    }

    void NodeFactory::RegisterNodes()
    {
        Register<MeshNode>();
        Register<MeshTransformNode>();
    }
}
