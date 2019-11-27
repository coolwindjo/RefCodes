#include <iostream>
#include <vector>
#include <array>
#include <type_traits>

using namespace std;

template<typename T>
struct has_resize
{
private:
	template<typename U> static char check(decltype(&(U::resize))*);
	template<typename U> static char check(typename add_pointer<decltype(declval<U>().resize(0))>::type p);
	template<typename U> static short check(...);

public:
	static constexpr int value = (sizeof(check<T>(0)) == sizeof(char));
};

template<typename T> void foo(T& c)
{
	//cout << has_resize<T>::value << ", " << typeid(T).name() << endl;
	if (has_resize<T>::value)
		cout << "T has resize" << endl;
	else
		cout << "T does not have resize" << endl;
}

/// array
template<typename T>
typename enable_if<!has_resize<T>::value, void>::type resize_imp(T& a, int n, int size)
{
	for (int i = n; i < size; ++i)
	{
		a[i] = 0;
	}
}
/// vector
template<typename T>
typename enable_if<has_resize<T>::value, void>::type  resize_imp(T& a, int n, int size)
{
	a.resize(n);
}

template<typename T>
void resize(T& a, int n)
{
	resize_imp(a, n, 10);
}

template<typename T>
struct ClassForTest
{
	void resize(T, T) {}
};

int main()
{
	//*	<= '/' �ϳ��� �����ּ���.

	ClassForTest<int> c;
	foo(c);	// ClassForTest�� resize �Լ��� ������ �ֽ��ϴ�. => ������ �մϴ�.

	vector<int> v = { 1,2,3,4,5 };
	array<int, 10> ar = { 1,2,3,4,5 };
	foo(v); // vector�� resize �Լ��� ������ �ֽ��ϴ�.	=> �������� �ʴ� ������ �ñ��մϴ�.
	foo(ar); // array �� resize �Լ��� �����ϴ�.

	/*/

	vector<int> v = { 1,2,3,4,5,6,7,8,9,10 };
	array<int, 10> ar = { 1,2,3,4,5 };
	resize(v, 3); // v�� ũ�Ⱑ 3���� ����Ǿ�� �մϴ�. 
				  // => vector�� ���ؼ� has_resize<T>�� �������� �ʾ�, ��������� Ʋ���� ���ɴϴ�.
	resize(ar, 3); // array�� resize�� �����Ƿ� 3��° ������Ĵ� 0���� ����ϴ�.

	for (auto n : v)
		cout << n << " "; // 1, 2, 3
	cout << endl;
	for (auto n : ar)
		cout << n << " "; // 1, 2, 3, 0, 0, 0, 0, 0, 0, 0

	//*/
	
	system("pause");
	return 0;
}