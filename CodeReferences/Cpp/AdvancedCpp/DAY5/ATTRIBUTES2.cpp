#include <iostream>

// [[nodiscard]] : �Լ� ��ȯ���� ���� ���� ��� ��� ���� �޶�� �ǹ�.. - C++17 ����
// [[nodiscard("message")]]  : C++20

[[nodiscard]] int* Alloc(std::size_t sz)
{
	return new int[10];
}

enum [[nodiscard]] ERRORCODE { WARNING, CRITICAL, FATAL };

ERRORCODE goo() { return FATAL; }

//[[�˼����¸��]] : ������ �ÿ� ����..(���)
[[clksajcfalsdajlskdl]]  void hoo() {}

int main()   
{
	goo();

	// �Ʒ� �ڵ��� �������� ?
	// ���ϰ��� �����ϸ� �ȵǴµ�.. �����ϰ� �ִ�..
	//Alloc(100);
}