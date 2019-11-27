#include <iostream>
#include <type_traits>

using namespace std;

/*
Function overloading matching priority
1. 정확한 형태
2. Template 버전
3. Type conversion 가능한 버전
4. 가변인자 버전
*/

//void foo(int n) { cout << "int" << endl; }
void foo(int* p) { cout << "int*" << endl; }
void foo(...) { cout << "..." << endl; }

/// is_abstract 만들기
struct Shape
{
	virtual void Draw() = 0;
};

template<typename T> char check(T (*p)[1]);	// { return 0; }
template<typename T> short check(...);		// {  return 0;  }

template<typename T> struct Is_abstract
{
	/// sizeof 는 어떤 함수가 쓰일 것인지 보고 return 값만 가지고 판단하므로 구현부가 없어도 됨
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