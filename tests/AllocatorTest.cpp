#include <gtest/gtest.h>
#include <map>
#include <set>
#include <vector>
#include "MyAllocator.h"
#include "MyContainer.h"

TEST(AllocatorTest, Map) {

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

	ASSERT_EQ(set, set2);
}

TEST(AllocatorTest, Vector) {

	std::vector<int, MyAllocator<int>> vec{1, 2, 3, 4, 5 };
	std::vector<int> vec2{ 1, 2, 3, 4, 5 };
	for (int i = 0; i < vec.size(); i++)
		ASSERT_EQ(vec[i], vec2[i]);
}

TEST(AllocatorTest, MyContainer) {

	MyContainer<int> my;
	ASSERT_FALSE(my.empty());
	MyContainer<int, MyAllocator<int>> my2;
	ASSERT_FALSE(my2.empty());
	int factorial = 1;
	for (int i = 0; i < 10; i++) {
		my.push_back(std::move(i)); //На MSVC почему то компилятор считает, что параметр push_back это rvalue reference
		my2.push_back(std::move(i)); //На MSVC почему то компилятор считает, что параметр push_back это rvalue reference
	}
	ASSERT_EQ(my.size(), my2.size());

	std::set <int> set;
	std::set <int> set2;
	for (auto it : my)
	{
		set.insert(it);
	}

	for (auto it : my2)
	{
		set2.insert(it);
	}

	ASSERT_EQ(set, set2);
}