#include <iostream>
#include <type_traits>

template<typename T, typename U >
struct PAIR
{
	// C++20 ���� EBCO ����� ���� ���� �����ϴ�.
	[[no_unique_address]] T first;
	[[no_unique_address]] U second;

	PAIR() = default;

	template<typename A, typename B>
	PAIR(A&& a, B&& b) : first(std::forward<A>(a)), second(std::forward<B>(b)) {}

	T& getFirst() { return first; }
	U& getSecond() { return second; }
};



int main()
{
	int* p1 = new int;
	int* p2 = (int*)malloc(4);

	// �Լ� �ּҿ� �����ڸ� ���� �����Ѵٰ� ������ ���ô�.

	auto d1 = [](int* p) { delete p; };
	auto d2 = [](int* p) { free(p); };

	PAIR<decltype(d1), int*> pair1(d1, p1);
	PAIR<decltype(d2), int*> pair2(d2, p2);

	// ���Ŀ� ������ �ʿ��ϸ�
	pair1.getFirst()(pair1.getSecond());

	// ��, �޸� �ּҿ� �����ڶ�� 2���� ������ �������..
	// �޸� ũ��� 4����Ʈ�� ���
	std::cout << sizeof(pair1) << std::endl; // 4

	// C++ǥ���� unique_ptr �� ���������� �츮�� ����
	// PAIR ���� Ŭ������ ����մϴ�.
}

// �򰡵������� ǥ���� �޾� ������
