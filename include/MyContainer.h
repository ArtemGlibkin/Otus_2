#pragma once
#include <memory>
#include <type_traits>
#include <functional>


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
	Alloc allocator;
	using Ptr = std::shared_ptr<Node<T>>;
	Ptr container_head = nullptr;
	Ptr* container_last = &container_head;
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

	void deleter(T* ptr)
	{
		allocator.deallocate(ptr, 1);
	}

	template<typename U>
	void push_back(U&& arg)
	{
		static_assert(std::is_same<std::decay_t<U>, std::decay_t<T>>::value, "U must be the same as T");
		Ptr& ptr = *container_last;
		ptr = Ptr(allocator.allocate(1), [&](Node<T>* ptr) {allocator.deallocate(ptr, 1); });//std::allocate_shared<Node<T>>(allocator);//Ptr(allocator.allocate(1)ò );
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
		return container_size;
	}
};
