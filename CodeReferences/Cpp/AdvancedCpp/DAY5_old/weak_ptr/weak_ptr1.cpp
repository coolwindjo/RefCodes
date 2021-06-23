#include <iostream>
#include <memory>

struct People
{

};

int main()
{
	std::shared_ptr<People> sp1(new People);
	std::shared_ptr<People> sp2 = sp1;	// 참조 계수 증가

	std::cout << sp2.use_count() << std::endl; // 2

	std::weak_ptr<People> wp = sp1;   // 가리킬수 있지만 참조계수 증가안함.
	
	std::cout << sp2.use_count() << std::endl; // 2
}