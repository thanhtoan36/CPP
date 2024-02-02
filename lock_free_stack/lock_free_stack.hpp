#pragma once

#include <atomic>

template <typename T>
class lock_free_stack
{
private:
    struct node
    {
        /* data */
        T data;
        node *next;
        node(const T &d) : data(d) {}
    };

    std::atomic<node*> head_;

public:
    void push(const T &data)
    {
        node *new_elem = new node(data);
        new_elem->next = head_.load();
        while (!head_.compare_exchange_weak(new_elem->next, new_elem));
    }

    T pop()
    {
        node *old_head = head_.load();
        while (!head_.compare_exchange_weak(old_head, old_head->next));
        T ret = old_head->data;
        delete old_head;
        return ret;
    }

    [[nodiscard]]bool is_empty() const noexcept
	{
		return head_.load() == nullptr;
	}
};