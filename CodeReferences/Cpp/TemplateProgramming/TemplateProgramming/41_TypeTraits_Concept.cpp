#include <iostream>

using namespace std;

/// C++ ǥ�� is_pointer
/// constexpr : Compile time �� ���Ǵ� ���
/// Primary template: false ����, value = false
template<typename T>
//class IsPointer { public:	enum { value = false }; };
//class IsPointer { public:	static constexpr bool value = false; };
struct IsPointer { static constexpr bool value = false; };
/// T �� Pointer �� ��츦 Partial specialization
/// Partial specialization: true ����, value = true
template<typename T>
//class IsPointer<T*> { public:	enum { value = true }; };
//class IsPointer<T*> { public:	static constexpr bool value = true; };
struct IsPointer<T*> { static constexpr bool value = true; };
/// ��� Pointer ����
template<typename T>
struct IsPointer<T* const> { static constexpr bool value = true; };

template<typename T> 
void foo1(const T& a) 
{ 
	//if (IsPointer<T>::value)	///< Meta function: Fuction that used in Compile time.
	if (is_pointer<T>::value)
	{
		cout << "T is a Pointer." << endl; 
	}
	else
	{
		cout << "T is not a Pointer." << endl; 
	}
}

/// is_array
template<typename T>
struct IsArray 
{ 
	static constexpr bool value = false;
	static constexpr int size = 0;	///< If it is not an array.
};
template<typename T, int N>
struct IsArray<T[N]> 
{ 
	static constexpr bool value = true;
	static constexpr int size = N;
};

template<typename T>
void foo2(const T& a) 
{ 
	//if (IsArray<T>::value)	///< Meta function: Fuction that used in Compile time.
	if(is_array<T>::value)
	{
		cout << "T is an Array and its size is " << IsArray<T>::size << endl; 
		//cout << "T is an Array and its size is " << is_array<T>::size << endl; 
	}
	else
	{
		cout << "T is not an Array." << endl; 
	}
}

int main()
{
	int n = 3;	///< int
	int arn[4] = { 3, 2, 1, 4 };	///< int[2], int[]�ʹ� �ٸ�

	foo1(n);
	foo1(&n);
	foo2(arn);

	system("pause");
	return 0;
}