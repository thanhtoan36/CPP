#pragma once

#include <unordered_map>
#include "event.h"
#include "event_types.h"

// Stores events in a map and enables routing of signals
template <typename Key = Events, typename... Ts>
class EventEmitter
{
private:
    using EventType = Event<Ts...>;
    using EventMap = std::unordered_map<Key, EventType>;

    EventMap event_map;

public:
    // Finds and returns an event pointer in the container by the given key.
    template <typename K>
    EventType *getEvent(K &&key)
    {
        auto it = event_map.find(std::forward<K>(key));
        return it != event_map.end() ? &it->second : nullptr;
    }

    // Finds and returns an event pointer in the container by the given key.
    template <typename K>
    const EventType *getEvent(K &&key) const
    {
        auto it = event_map.find(std::forward<K>(key));
        return it != event_map.end() ? &it->second : nullptr;
    }

    // Inserts a new event if one does not exist yet.
    // Returns the existing event if it already exists.
    template <typename K>
    EventType *event(K &&key)
    {
        auto *const ptr = getEvent(std::forward<K>(key));
        if (!ptr)
        {
            return &(event_map.insert(typename EventMap::value_type(std::forward<K>(key), EventType())).first->second);
        }
        return ptr;
    }

    // Connects a given callback to a given event.
    // Inserts a new event if one does not already exist.
    template <typename K, typename CB>
    decltype(auto) on(K &&key, CB &&callback)
    {
        return event(std::forward<K>(key))->connect(std::forward<CB>(callback));
    }

    // Emits the event for a given key, using the given arguments.
    template <typename K, typename... Args>
    void emit(K &&key, Args &&...args) const
    {
        const auto *const ptr = getEvent(std::forward<K>(key));
        if (ptr)
        {
            ptr->emit(std::forward<Args>(args)...);
        }
    }

    // Returns the number of connections for a given event.
    template <typename K>
    std::size_t getConnectionCount(K &&key) const
    {
        const auto *const ptr = getEvent(std::forward<K>(key));
        if (ptr)
        {
            return ptr->size();
        }

        // If there is no event, then the size is zero
        return 0u;
    }

    // Returns true if there are callbacks on the given event.
    template <typename K>
    bool isConnected(K &&key) const
    {
        const auto *const ptr = getEvent(std::forward<K>(key));
        if (ptr)
        {
            return !ptr->isConnected();
        }

        // If there is no event then it is alway disconnected.
        return false;
    }
};
