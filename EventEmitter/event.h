#pragma once

#include <vector>
#include <atomic>
#include <functional>
#include <mutex>

// Event handler
template <typename... Ts>
class Event
{
public:
    using ID = uint64_t;
    using Callback = std::function<void(Ts...)>;
    using CallbackIDPair = std::pair<Callback, ID>;
    using CallbackContainer = std::vector<CallbackIDPair>;
    using EventType = Event<Ts...>;

private:
    // Counts up to create new unique IDs.
    std::atomic<ID> id_counter;

    // Holds all of the active callbacks.
    mutable CallbackContainer callbacks;

public:
    Event()
    {
        id_counter.store(0u);
    }

    Event(const EventType &other)
    {
        id_counter.store(0u);
        copyConnections(other);
    }

    Event(EventType &&other) noexcept
    {
        id_counter.store(other.id_counter);
        callbacks = std::move(other.callbacks);
    }

    EventType &operator=(const EventType &other)
    {
        if (this != &other)
        {
            id_counter.store(0u);
            copyConnections(other);
        }
        return *this;
    }

    EventType &operator=(EventType &&other)
    {
        if (this != &other)
        {
            id_counter.store(other.id_counter);
            callbacks = std::move(other.callbacks);
        }
        return *this;
    }

    // Removes a callback from the container.
    // Must not be called from inside the emit events chain.
    void disconnect(const ID &id) const
    {
        for (std::size_t i = 0u; i < callbacks.size(); ++i)
        {
            if (callbacks.at(i).second == id)
            {
                // Remove the element from the container.
                callbacks.erase(callbacks.begin() + i);
                return;
            }
        }
    }

    // Creates a connection that gets called for every emit.
    template <typename F>
    decltype(auto) connect(F &&callback)
    {
        const auto id = ++id_counter;
        callbacks.emplace_back(std::forward<F>(callback), id);
        return [&, id]
        { disconnect(id); };
    }

    // Copies the callbacks from a given event to this event.
    // New IDs are created as needed on this event.
    void copyConnections(const EventType &other)
    {
        for (const auto &pair : other.callbacks)
        {
            connect(pair.first);
        }
    }

    // Emits this event and calls all connections with given parameters.
    // This is unsafe because if a callback modifies the callback container
    // there could be undefined behavior.
    template <typename... Args>
    void emit(Args &&...args) const
    {
        for (auto &pair : callbacks)
        {
            pair.first(std::forward<Args>(args)...);
        }
    }

    // Returns true if there is at least one callback on this event.
    bool isConnected() const
    {
        return !callbacks.empty();
    }

    // Returns the number of callbacks on this event.
    std::size_t getConnectionCount() const
    {
        return callbacks.size();
    }
};
