// Allocator.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <list>
#include <set>
#include "MyAllocator.h"
#include "MyContainer.h"
#include "factorial.h"


int main()
{
	std::map <int, int> map;
	std::map <int, int, std::less<int>, MyAllocator<std::pair<int, int>>> map2;
	MyContainer<int> my;
	MyContainer<int, MyAllocator<int>> my2;
	int factorial = 1;
	for (int i = 0; i< 10; i++)	{
		factorial *= i <= 1 ? 1 : i;
		map.insert({ i, factorial });
		map2.insert({ i, factorial });
		my.push_back(std::move(i)); //На MSVC почему то компилятор считает, что параметр push_back это rvalue reference
		my2.push_back(std::move(i)); //На MSVC почему то компилятор считает, что параметр push_back это rvalue reference
	}

	for (auto& it : map) {
		std::cout << it.first << "	" << it.second << std::endl;
	}

	for (auto& it : my2)
	{
		std::cout << it << std::endl;
	}

	/*
	std::map <int, int, std::less<int>, MyAllocator<std::pair<int, int>> > map;
	std::map <int, int> map2;
	
	for (int i = 0; i < 70; i++)
	{
		map.insert({ i, i });
		map2.insert({ i, i });
	}

	std::set < std::pair<int, int>> set;
	std::set < std::pair<int, int>> set2;
	for (auto it : map)
	{
		set.insert(it);
	}

	for (auto it : map2)
	{
		set2.insert(it);
	}

	if (set == set2)
		std::cout << "test complete" << std::endl;

	try
	{
		MyContainer<int, MyAllocator<int>> container;
		container.push_back(1);
		container.push_back(5);
		container.push_back(3);
		std::cout << (container.empty() ? "true" : "false") << std::endl;
		std::cout << "size " << container.size() << std::endl;
		container.push_back(2);
		container.pop_front();
		container.pop_front();
		std::cout << "size "<< container.size() << std::endl;
		for (auto i : container)
		{
			std::cout << i << std::endl;
		}
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	*/
}
