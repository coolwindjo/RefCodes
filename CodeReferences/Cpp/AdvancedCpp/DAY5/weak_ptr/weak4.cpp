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

	}// sp2�� �ı�...

	if ( sp1->bestFriend.expired() )
	{
		std::cout << "��ü �ı���.." << std::endl;
	}

}
// unique_ptr : �ڿ� ����.. ���� ��밡��

// shared_ptr : �ڿ� ����
//			    �ڿ� ���� ���� ������ ����..
//		        ���� ��� �ִ� ���� �ڿ��� �ı��ɼ� ����.

// weak_ptr : �ڿ� ���� ���� ���� ����.
//				�ڿ� �ı� ���� ����

// raw pointer : �ڿ� ���� ���� ���� ����
//				�ڿ� �ı� ���� ����..