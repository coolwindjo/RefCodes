#include <iostream>
#include <vector>
#include <type_traits>

using namespace std;

namespace True_type_False_type
{
/// IsArray implementation
template<typename T>
struct IsArray	: false_type
{
	static constexpr int size = 0;
};
template<typename T, int N>
struct IsArray<T[N]>	: true_type
{
	static constexpr int size = N;
};

/// Array
template<typename T>
void resize_imp(T& a, int n, int size, true_type)
{
	for (int i = n; i < size; ++i)
	{
		a[i] = 0;
	}
}
/// Except array => vector
template<typename T>
void resize_imp(T& a, int n, int size, false_type)
{
	a.resize(n);
}

template<typename T>
void resize(T& a, int n)
{
	resize_imp(a, n, IsArray<T>::size, IsArray<T>());
}
}	// namespace True_type_False_type

namespace Enable_if
{
/// IsArray implementation
template<typename T>
struct IsArray
{
	static constexpr bool value = false;
	static constexpr int size = 0;
};
template<typename T, int N>
struct IsArray<T[N]>
{
	static constexpr bool value = true;
	static constexpr int size = N;
};

/// Array
template<typename T>
typename enable_if<IsArray<T>::value, void>::type resize_imp(T& a, int n, int size)
{
	for (int i = n; i < size; ++i)
	{
		a[i] = 0;
	}
}
/// Except array => vector
template<typename T>
typename enable_if<!IsArray<T>::value, void>::type  resize_imp(T& a, int n, int size)
{
	a.resize(n);
}

template<typename T>
void resize(T& a, int n)
{
	resize_imp(a, n, IsArray<T>::size);
}
}	// namespace Enable_if

int main()
{
	int x[10] = { 1,2,3,4,5,6,7,8,9,10 };
	vector<int> v = { 1,2,3,4,5,6,7,8,9,10 };

	if (false) 
	{
		using namespace True_type_False_type;
		resize(v, 3); // v의 크기가 3으로 변경됩니다.
		resize(x, 3); // 배열의 크기는 변경할 수 없으므로 3번째 요소이후는 0으로 만듭니다.
	}
	else 
	{
		using namespace Enable_if;
		resize(v, 3); // v의 크기가 3으로 변경됩니다.
		resize(x, 3); // 배열의 크기는 변경할 수 없으므로 3번째 요소이후는 0으로 만듭니다.
	}

	for (auto n : v)
		cout << n << " "; // 1, 2, 3
	cout << endl;
	for (auto n : x)
		cout << n << " "; // 1, 2, 3, 0, 0, 0, 0, 0, 0, 0

	system("pause");
	return 0;
}