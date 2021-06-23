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

		// ���� bestFriend�� ��¥ ������ �Դϴ�.
		sp1->bestFriend = sp2.get();
		sp2->bestFriend = sp1.get();

	}// sp2�� �ı�...

	if (sp1->bestFriend != 0)
	{
		// bestFriend �� ����Ű�� ���� ��ȿ�ҰŶ�� �����Ҽ� ������...
		// ��ü�� �ı� �Ǿ���.
		// danging pointer
	}
	
}