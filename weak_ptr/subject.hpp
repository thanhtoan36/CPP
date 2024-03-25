#pragma once
#include <memory>
#include <forward_list>
#include <functional>

template <typename... Args>
class Subject
{
public:
    using Observer = std::shared_ptr<std::function<void(Args...)>>;
    using ObserverContainer = std::forward_list<std::weak_ptr<std::function<void(Args...)>>>;

    Subject() {}

    void notify(Args &&...args)
    {
        bool cleanup = false;
        for (const auto &observer_weak : m_observers)
        {
            if (const auto &observer_function = observer_weak.lock())
            {
                (*observer_function)(std::forward<Args>(args)...);
            }
            else
            {
                // weak pointer expired, do a cleanup round
                cleanup = true;
            }
        }

        if (cleanup)
        {
            m_observers.remove_if([](auto observer)
                                  { return observer.expired(); });
        }
    }

    /**
     * Register a function as observer. Keep the returned shared_ptr around as long as you want
     * the function to be called.
     */
    Observer makeObserver(std::function<void(Args...)> observerFunction)
    {
        auto observer = std::make_shared<std::function<void(Args...)>>(observerFunction);
        m_observers.emplace_front(observer);
        return observer;
    }

private:
    ObserverContainer m_observers;
};