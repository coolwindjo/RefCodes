#include <iostream>
#include <memory>

struct People
{
	~People() { std::cout << "~People" << std::endl; }

	// std::shared_ptr<People> bestFriend;
	// People* bestFriend;	// raw pointer

	std::weak_ptr<People> bestFriend; // 참조계수 증가 안함.
									// 객체 파괴 조사 가능.
};

int main()
{
	std::shared_ptr<People> sp1(new People);
	{
		std::shared_ptr<People> sp2(new People);

		// weak_ptr은 shared_ptr과 호환
		sp1->bestFriend = sp2;
		sp2->bestFriend = sp1;

	}

	if ( ! sp1->bestFriend.expired() )
	{
		// wp 는 객체 접근이 안됩니다.
		// wp 는 -> 연산 없음.
		//sp1->bestFriend->멤버함수(); // error

		// 이제 접근하고 싶은면 
		std::shared_ptr<People> sp = wp.lock();

		if (sp)
		{
			sp->접근....
		}


	}
}

// smkang @ codenuri.co.kr









