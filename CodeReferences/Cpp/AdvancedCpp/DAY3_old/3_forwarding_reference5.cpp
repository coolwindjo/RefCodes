#include <iostream>
#include <vector>

int main()
{
	std::vector<int> v1 = { 1,1,1,1,1 };

	for (auto& n : v1) 
		n = 0;

	//---------------------------------------
	std::vector<bool> v2 = { 1,1,1,1,1 };

//	for (auto& n : v2) // error
	for (auto&& n : v2)// ok
		n = 0;
}