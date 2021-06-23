#include <iostream>
#include <iterator>
#include <vector>
#include <list>

// advance �����
template<typename T> requires std::input_iterator<T>
void advance(T& p, int N)
{
	std::cout << "++�� �̵�" << std::endl;
	while (N--) ++p;
}

template<typename T> requires std::random_access_iterator<T>
void advance(T& p, int N)
{
	std::cout << "+�� �̵�" << std::endl;
	p = p + N;
}

template<typename T> requires std::random_access_iterator<T>
void sort(T first, T last)
{
	std::cout << "random" << std::endl;
}

template<typename T> requires std::bidirectional_iterator<T>
void sort(T first, T last)
{
	std::cout << "bidirectional_iterator" << std::endl;
}

int main()
{
//	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10 }; // �������� �ݺ���, ++ �� + ��� ����.
	std::list<int>   v = { 1,2,3,4,5,6,7,8,9,10 }; // ����� �ݺ���, ++, -- �� ����
	//												// �Է� �ݺ���,  ++ �� ����
	auto p = v.begin();

	// p�� 5ĭ �����ϰ� �ʹ�..
	// p = p + 5 ; // vector �϶��� ok.. list ��� ����
	//++p; ++p; ++p; ++p; ++p; // ��� ok.. ������ vector��� ������.!
	advance(p, 5); // ok.. �ּ��� �ڵ�

	sort(v.begin(), v.end()); // vector��� ok.. list �� error
								// v.sort() list�� ���.
}