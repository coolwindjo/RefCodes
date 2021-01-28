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

	}// sp2는 파괴...

	if ( sp1->bestFriend.expired() )
	{
		std::cout << "객체 파괴됨.." << std::endl;
	}

}
// unique_ptr : 자원 독점.. 나만 사용가능

// shared_ptr : 자원 공유
//			    자원 수명에 대한 강력한 권한..
//		        내가 살아 있는 동안 자원은 파괴될수 없다.

// weak_ptr : 자원 수명에 대한 권한 없음.
//				자원 파괴 조사 가능

// raw pointer : 자원 수명에 대한 권한 없음
//				자원 파괴 조사 못함..