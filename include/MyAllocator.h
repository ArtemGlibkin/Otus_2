
#pragma once
#include <memory>


template <typename T>
struct MyAllocator {
	using value_type = T;
	using size_ptr = std::shared_ptr<uint32_t>;
	using memory_ptr = std::shared_ptr<uint8_t[]>;
	memory_ptr memory = nullptr;

	//Storing sizes in shared_ptr is required for the copy constructor to work properly
	size_ptr chunk_size = std::make_shared<uint32_t>(100 * 128);
	size_ptr capacity;

	MyAllocator()
	{
		memory = memory_ptr(new uint8_t[*chunk_size]);
		capacity = std::make_shared<uint32_t>(0);
	}

	template <typename U>
	MyAllocator(const MyAllocator<U>& copy)
	{
		memory = copy.memory;
		capacity = copy.capacity;
		chunk_size = copy.chunk_size;
	}

	T* allocate(std::size_t n) {

		unsigned int object_size = sizeof(T) * n;

		if (*capacity == 0 && object_size >= *chunk_size)
		{
			*chunk_size = object_size * 2;
			memory = memory_ptr(new uint8_t[*chunk_size]);
		}
		else if (*capacity.get() + object_size >= *chunk_size)
			throw std::runtime_error("The memory is filled in");

		T* ret = reinterpret_cast<T*>(memory.get() + *capacity.get());
		*capacity.get() += object_size;

		return ret;
	}

	/*
		It will only work normally on a vector when memory is deleted and allocated at once. 
		In other cases memory will be idle without the possibility of reuse.
		As a solution: keep a list of pointer-size memory structures and check the list at each new allocate
	*/
	void deallocate(T* p, std::size_t n) {

		if (n * sizeof(T) == *capacity)
		{
			*capacity == 0; 
		}
	}
};