
#include "EventDispatcher.h"

namespace Oedon::Editor
{

    Editor::EventDispatcher::EventDispatcher() :
        _arenas{},
        _tokens{1}
    {
    }

    Editor::EventDispatcher::~EventDispatcher()
    {
        for(auto& arena : _arenas)
        {
            delete arena.second;
        }
    }
}
