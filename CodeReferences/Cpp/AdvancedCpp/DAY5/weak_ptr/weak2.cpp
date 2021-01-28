#include <iostream>
#include <memory>

struct People
{
	~People() { std::cout << "~People" << std::endl; }

	std::shared_ptr<People> bestFriend;
};

int main()
{
	std::shared_ptr<People> sp1(new People);
	std::shared_ptr<People> sp2(new People);
	
	// 아래 코드는 상호 참조 현상이 나타납니다
	// 메모리 누수 입니다.
	sp1->bestFriend = sp2;
	sp2->bestFriend = sp1;
}