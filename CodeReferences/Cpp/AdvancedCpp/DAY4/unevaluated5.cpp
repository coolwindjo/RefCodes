#include <iostream>

class Test
{
public:
	Test(int a) {}
	void resize() {}
};

// �򰡵��� ���� ǥ���Ŀ����� ����Ѵٸ� ���� ������ �ȴ�.
// �������� ��翡 ������� �򰡵��� ���� ǥ���Ŀ��� ����� ��ü�� �ʿ��� ���
// �Ʒ� �Լ� ���.
template<typename T> T declval();


//template<typename T> int  check(decltype( T().resize())* p); // T�� ����Ʈ �����ڰ� �ʿ�

template<typename T> int  check(decltype( std::declval<Test>().resize() )* p);


template<typename T> char check(...);

int main()
{
	int n = sizeof(check<Test>(0));

	std::cout << n << std::endl;
}



