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
	//*	<= '/' 하나를 지워주세요.

	ClassForTest<int> c;
	foo(c);	// ClassForTest는 resize 함수를 가지고 있습니다. => 정상동작 합니다.

	vector<int> v = { 1,2,3,4,5 };
	array<int, 10> ar = { 1,2,3,4,5 };
	foo(v); // vector는 resize 함수를 가지고 있습니다.	=> 동작하지 않는 이유가 궁금합니다.
	foo(ar); // array 는 resize 함수가 없습니다.

	/*/

	vector<int> v = { 1,2,3,4,5,6,7,8,9,10 };
	array<int, 10> ar = { 1,2,3,4,5 };
	resize(v, 3); // v의 크기가 3으로 변경되어야 합니다. 
				  // => vector에 대해서 has_resize<T>가 동작하지 않아, 최종결과도 틀리게 나옵니다.
	resize(ar, 3); // array는 resize가 없으므로 3번째 요소이후는 0으로 만듭니다.

	for (auto n : v)
		cout << n << " "; // 1, 2, 3
	cout << endl;
	for (auto n : ar)
		cout << n << " "; // 1, 2, 3, 0, 0, 0, 0, 0, 0, 0

	//*/
	
	system("pause");
	return 0;
}