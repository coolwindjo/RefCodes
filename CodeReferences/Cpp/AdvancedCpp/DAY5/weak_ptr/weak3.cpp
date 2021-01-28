#include <iostream>
#include <memory>

struct People
{
	~People() { std::cout << "~People" << std::endl; }

	//std::shared_ptr<People> bestFriend;
	People* bestFriend;	// raw pointer
};

int main()
{
	std::shared_ptr<People> sp1(new People);
	{
		std::shared_ptr<People> sp2(new People);

		// 이제 bestFriend은 진짜 포인터 입니다.
		sp1->bestFriend = sp2.get();
		sp2->bestFriend = sp1.get();

	}// sp2는 파괴...

	if (sp1->bestFriend != 0)
	{
		// bestFriend 가 가리키는 곳이 유효할거라고 생각할수 있지만...
		// 객체는 파괴 되었다.
		// danging pointer
	}
	
}