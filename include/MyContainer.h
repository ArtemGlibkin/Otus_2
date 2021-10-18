#pragma once
#include <memory>

template <typename T>
struct Node
{
	T element;
	std::shared_ptr<Node<T>> next = nullptr;
};

template <typename T, typename Alloc = std::allocator<Node<T>>>
class MyContainer
{
private:

	using Ptr = std::shared_ptr<Node<T>>;
	Ptr container_head = nullptr;
	Ptr* container_last = &container_head;
	Alloc allocator;
	size_t container_size = 0;

public:
	struct Iterator
	{
		Iterator(const Ptr& ptr) : m_ptr(ptr) {};
		T& operator*() const { return m_ptr->element; }
		T* operator->() { return &m_ptr->element; }

		Iterator& operator++() { m_ptr = m_ptr->next; return *this; }
		Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
		friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
		friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };
	private:
		Ptr m_ptr;
		friend class MyContainer;
	};

	Iterator begin()
	{
		return Iterator(container_head);
	}

	Iterator end()
	{
		return Iterator(*container_last);
	}

	MyContainer() = default;

	void push_back(T&& arg)
	{
		Ptr& ptr = *container_last;
		ptr = std::allocate_shared<Node<T>>(allocator);
		ptr->element = arg;
		container_last = &ptr->next;
		container_size += 1;
	}

	T pop_front()
	{
		if (!container_head)
			throw std::runtime_error("empty container");

		T ret = std::move(container_head->element);
		container_head = container_head->next;
		container_size -= 1;
		return ret;
	}

	size_t size()
	{
		return container_size;
	}

	bool empty()
	{
		return container_head == nullptr ? true : false;
	}
};
