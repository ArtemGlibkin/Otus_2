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
		my.push_back(i); 
		my2.push_back(i);
	}

	for (auto& it : map) {
		std::cout << it.first << "	" << it.second << std::endl;
	}

	for (auto& it : my2)
	{
		std::cout << it << std::endl;
	}

}
