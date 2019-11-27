#include <iostream>
#include <type_traits>

using namespace std;

/*
Function overloading matching priority
1. ��Ȯ�� ����
2. Template ����
3. Type conversion ������ ����
4. �������� ����
*/

//void foo(int n) { cout << "int" << endl; }
void foo(int* p) { cout << "int*" << endl; }
void foo(...) { cout << "..." << endl; }

/// is_abstract �����
struct Shape
{
	virtual void Draw() = 0;
};

template<typename T> char check(T (*p)[1]);	// { return 0; }
template<typename T> short check(...);		// {  return 0;  }

template<typename T> struct Is_abstract
{
	/// sizeof �� � �Լ��� ���� ������ ���� return ���� ������ �Ǵ��ϹǷ� �����ΰ� ��� ��
	//enum { value = (sizeof(check<T>(0)) == sizeof(short)) };
	static constexpr int value = (sizeof(check<T>(0)) == sizeof(short));
};

int main()
{
	foo(0);

	cout << boolalpha;
	cout << Is_abstract<Shape>::value << endl;

	system("pause");
	return 0;
}