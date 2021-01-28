#include <iostream>
#include <string>
#include <vector>

// �� move�� �߿��Ѱ� ? 
// Algorithm �ۼ��� "����" ���ٴ� "move" ��
// ���� ��찡 �����ϴ�.

// ������ move�� ����� Program ������ ��� ��ų �� �ֽ��ϴ�.

// move: �ᱹ �ּҸ� �ű�� ����
// �׷���, �ּҸ� �ű�� ���� ��� Type�� �����ϴ� "�Ϲ����� ����"�� ź��!

// �Ʒ� Swap�� ���� ����� �Լ� �Դϴ�.
// // template<typename T>
// // void Swap(T& a, T& b)
// // {
// // 	T tmp = a;
// // 	a = b;
// // 	b = tmp;
// }

template<typename T>
void Swap(T& a, T& b)
{
	T tmp = std::move(a);
	a = std::move(b);
	b = std::move(tmp);
}

int main()
{
	std::string s1 = "hello";
	std::string s2 = "world";
	Swap(s1, s2);
}



