
#pragma once
#include <memory>


template <typename T>
struct MyAllocator {
	using value_type = T;
	using size_ptr = std::shared_ptr<uint32_t>;
	using memory_ptr = std::shared_ptr<uint8_t[]>;
	memory_ptr memory = nullptr;

	//Хранение размеров в shared_ptr требуется, чтобы нормально работал конструктор копирования
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

		/*
			Увеличить размер выделяемой памяти даем, когда вся память пустая;
		*/
		if (*capacity == 0 && object_size >= *chunk_size)
		{
			*chunk_size *= 2;
			memory.swap(memory_ptr(new uint8_t[*chunk_size]));
		}
		else if (*capacity.get() + object_size >= *chunk_size)
			throw std::runtime_error("The memory is filled in");

		T* ret = reinterpret_cast<T*>(memory.get() + *capacity.get());
		*capacity.get() += object_size;

		return ret;
	}

	/*
		Нормально будет работать только на векторе, когда память удаляется и выделяется сразу. 
		В остальных случаях память будет простаивать без возможности повторного использования.
		Как решение: хранить список структур указатель-размер памяти и при каждом новом allocate проверять список
	*/
	void deallocate(T* p, std::size_t n) {

		if (n * sizeof(T) == *capacity)
		{
			*capacity == 0; 
		}
	}
};