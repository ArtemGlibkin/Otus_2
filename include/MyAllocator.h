
#pragma once
#include <memory>


template <typename T , size_t size = 12800>
struct MyAllocator {
	int unique_number = 1;
	using value_type = T;
	using size_ptr = std::shared_ptr<uint32_t>;
	using memory_ptr = std::shared_ptr<uint8_t[]>;
	memory_ptr memory;

	//Storing sizes in shared_ptr is required for the copy constructor to work properly
	size_ptr chunk_size = std::make_shared<uint32_t>(size);
	size_ptr capacity = std::make_shared<uint32_t>(0);

	MyAllocator()
	{
		std::cout << "Constructor with unique_number " << unique_number << std::endl << std::endl;
	}

	template <typename U>
	MyAllocator(const MyAllocator<U>& copy)
	{
		unique_number = copy.unique_number + 1;
		std::cout << "Copy constructor with unique_number " << unique_number << std::endl << std::endl;
	}
	~MyAllocator()
	{
		std::cout << "Destructor with unique_number " << unique_number << std::endl;
		std::cout << "Begin address " << (T*)memory.get() << std::endl << std::endl;
	}

	template <typename U>
	struct rebind {
		using other = MyAllocator<U>;
	};

	void print()
	{
		std::cout << "Allocate with unique_number " << unique_number << std::endl;
		std::cout << "Capacity " << *capacity.get() << std::endl;
		//std::cout << "Memory " << memory.get() << std::endl;

	}

	T* allocate(std::size_t n) {
		print();
		std::cout << "Allocate " << n << std::endl;
		unsigned int object_size = sizeof(T) * n;

		if (*capacity == 0)
		{
			if(object_size >= *chunk_size)
				*chunk_size = object_size * 2;
			memory = memory_ptr(new uint8_t[*chunk_size]);
		}
		else if (*capacity.get() + object_size >= *chunk_size)
			throw std::runtime_error("The memory is filled in");

		T* ret = reinterpret_cast<T*>(memory.get() + *capacity.get());
		*capacity.get() += object_size;
		std::cout << "Return " << ret << std::endl << std::endl;;
		return ret;
	}

	/*
		It will only work normally on a vector when memory is deleted and allocated at once. 
		In other cases memory will be idle without the possibility of reuse.
		As a solution: keep a list of pointer-size memory structures and check the list at each new allocate
	*/
	void deallocate(T* p, std::size_t n) {

		std::cout << "Deallocate " << p << " Unique number " << unique_number << std::endl;
		if (n * sizeof(T) == *capacity)
		{
			*capacity == 0; 
		}
	}
};