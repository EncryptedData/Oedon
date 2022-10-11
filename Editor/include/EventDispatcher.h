#pragma once

#include <unordered_map>
#include <type_traits>
#include <typeindex>
#include <functional>
#include <vector>
#include <cinttypes>

namespace Oedon::Editor
{
    using EventToken = std::uint64_t;

    template<typename EventType>
    using EventListener = std::function<void(EventType&)>;

    class EventDispatcher
    {
    public:

        explicit EventDispatcher();

        ~EventDispatcher();

        template<typename EventType>
        EventToken Register(const EventListener<EventType>& listener)
        {
            ListenerArena<EventType>& arena = GetArena<EventType>();

            EventToken token = _tokens++;

            Listener<EventType> list;
            list.listener = listener;
            list.token = token;

            arena.listeners.emplace_back(list);

            return token;
        }

        template<typename EventType>
        void Fire(EventType& event)
        {
            ListenerArena<EventType>& arena = GetArena<EventType>();

            for(const Listener<EventType>& listener : arena.listeners)
            {
                listener.listener(std::ref(event));
            }
        }

        template<typename EventType>
        void Unregister(EventToken token)
        {
            ListenerArena<EventType>& arena = GetArena<EventType>();

            auto it = std::find_if(arena.listeners.begin(), arena.listeners.end(), [&](const Listener<EventType>& a){
                return a.token == token;
            });

            if(it != arena.listeners.end())
            {
                arena.listeners.erase(it);
            }
        }

    private:
        template<typename EventType>
        struct Listener
        {
            EventListener<EventType> listener;
            EventToken token;
        };

        struct BaseListenerArena
        {
            virtual ~BaseListenerArena() = default;
        };

        template<typename EventType>
        struct ListenerArena : public BaseListenerArena
        {
            std::vector<Listener<EventType>> listeners;

            virtual ~ListenerArena() override = default;
        };

        std::unordered_map<std::type_index, BaseListenerArena*> _arenas;
        EventToken _tokens;

        template<typename EventType>
        ListenerArena<EventType>& GetArena()
        {
            auto index = std::type_index(typeid(EventType));

            auto it = _arenas.find(index);

            if(it != _arenas.end())
            {
                return *reinterpret_cast<ListenerArena<EventType>*>(it->second);
            }

            auto arena = new ListenerArena<EventType>;
            _arenas[index] = arena;

            return *arena;
        }
    };

    template<typename EventType>
    class ListenFor
    {
    public:
        explicit ListenFor(EventDispatcher* dispatcher) :
            _dispatcher{dispatcher}
        {
            using namespace std::placeholders;
            _token = _dispatcher->Register<EventType>(std::bind(&ListenFor::OnEvent, this, _1));
        }

        ~ListenFor()
        {
            _dispatcher->Unregister<EventType>(_token);
        }

        virtual void OnEvent(EventType& event) = 0;

    private:
        EventDispatcher* _dispatcher;
        EventToken _token;
    };
}
