
#pragma once
#include <memory>


template <typename T>
struct MyAllocator {
	using value_type = T;
	std::shared_ptr<uint8_t[]> memory = nullptr;
	static const unsigned int chunk_size = 100 * 128;
	std::shared_ptr<uint32_t> capacity;

	MyAllocator()
	{
		memory = std::shared_ptr<uint8_t[]>(new uint8_t[chunk_size]);
		capacity = std::make_shared<uint32_t>(0);
	}

	template <typename U>
	MyAllocator(const MyAllocator<U>& copy)
	{
		memory = copy.memory;
		capacity = copy.capacity;
	}

	T* allocate(std::size_t n) {

		unsigned int object_size = sizeof(T) * n;
		if (*capacity.get() + object_size >= chunk_size)
			throw std::runtime_error("The memory is empty");

		T* ret = reinterpret_cast<T*>(memory.get() + *capacity.get());
		*capacity.get() += object_size;

		return ret;
	}

	void deallocate(T* p, std::size_t) {
		//Do nothing
	}
};