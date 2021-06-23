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
	
	// �Ʒ� �ڵ�� ��ȣ ���� ������ ��Ÿ���ϴ�
	// �޸� ���� �Դϴ�.
	sp1->bestFriend = sp2;
	sp2->bestFriend = sp1;
}