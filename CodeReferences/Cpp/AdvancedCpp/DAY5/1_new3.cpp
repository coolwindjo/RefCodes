#include "cppmaster.h"
#include <vector>

class DBConnect {};

int main()
{
	// DBConnect �� �����ڿ��� DB�� �����Ѵٰ� ������ ������
	std::vector<DBConnect> v(5);

	v.resize(3); // �̼����� �ڵ� ������ ������ ���ô�.
				// �پ�� 2���� ��ü�� ����
				// �޸𸮴� �ı����� ������
				// "�Ҹ��ڴ� ��������� ȣ���ؼ� DB disconnect"

	v.resize(4); // �߰��� ��ü�� ���� �޸𸮴� �̹� �ֽ��ϴ�.
				// ������, �����ڸ� �ٽ� ȣ���ؼ�
				// DB�� �����ؾ� �մϴ�.
				// "�������� ����� ȣ���� �ʿ� �մϴ�."


}






/*
int main()
{
	std::vector<int> v(10);

	v.resize(7);

	std::cout << v.size() << std::endl; // 7
	std::cout << v.capacity() << std::endl; // 10

	v.push_back(0); // ���� �Ѱ� �߰�

	std::cout << v.size() << std::endl;     // 8
	std::cout << v.capacity() << std::endl; // 10

	v.shrink_to_fit(); // �ʿ���� ������ �޸� ����

	std::cout << v.size()     << std::endl; // 8
	std::cout << v.capacity() << std::endl; // 8

	v.push_back(0); // ���� �Ѱ� �߰�

	std::cout << v.size() << std::endl;     // 9
	std::cout << v.capacity() << std::endl; // 12
}
*/