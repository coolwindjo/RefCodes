#include <iostream>
#include <memory>

struct People
{
	~People() { std::cout << "~People" << std::endl; }

	// std::shared_ptr<People> bestFriend;
	// People* bestFriend;	// raw pointer

	std::weak_ptr<People> bestFriend; // ������� ���� ����.
									// ��ü �ı� ���� ����.
};

int main()
{
	std::shared_ptr<People> sp1(new People);
	{
		std::shared_ptr<People> sp2(new People);

		// weak_ptr�� shared_ptr�� ȣȯ
		sp1->bestFriend = sp2;
		sp2->bestFriend = sp1;

	}

	if ( ! sp1->bestFriend.expired() )
	{
		// wp �� ��ü ������ �ȵ˴ϴ�.
		// wp �� -> ���� ����.
		//sp1->bestFriend->����Լ�(); // error

		// ���� �����ϰ� ������ 
		std::shared_ptr<People> sp = wp.lock();

		if (sp)
		{
			sp->����....
		}


	}
}

// smkang @ codenuri.co.kr









