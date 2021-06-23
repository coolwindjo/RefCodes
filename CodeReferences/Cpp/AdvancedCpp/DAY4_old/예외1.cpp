// 예외1
#include <iostream>
#include <string>
#include <type_traits>

// 예외 : try~catch,  throw 키워드.
// noexcept
// 1. 특정 함수가 예외가 있는지 없는지 조사할때 사용 : noexcept( 함수호출식 )
// 2. 함수 선언의 뒤쪽에 붙여서 "함수가 예외 없음"을 알릴때 사용
void f1() noexcept
{
	int a = 10;
	a = 20;
}
void f2()
{
	// 이 안에서 발생하는 모든 예외를 catch 로 잡아서 처리후
	// 외부에 다시 throw 하지 않은 경우는 noexcept를 가능.
	int* p = new int[10]; // 메모리 부족시 std::bad_alloc 이라는 예외가 throw 됩니다.
	//if (p == 0) {}
	delete[] p;
}
// f3은 예외가 없을까요 ? 있을까요 ?
//void f3() noexcept // 예외가 없다.
//void f3() noexcept(true) // 예외가 없다.
//void f3() noexcept(false) // 예외가 있다

void f3() noexcept(std::is_nothrow_constructible_v<std::string> && 
		           std::is_nothrow_copy_constructible_v<std::string>)
{
	std::string s1 = "AA";
	std::string s2 = s1;
}

void f4() noexcept( noexcept( f3() ) )
{
	f3();
}

int main()
{
	bool b1 = noexcept( f1() );

	std::cout << b1 << std::endl;
	
	bool b2 = std::is_nothrow_constructible_v<std::string>;
	bool b3 = std::is_nothrow_copy_constructible_v<std::string>;

	std::cout << b2 << std::endl;
	std::cout << b3 << std::endl;
}


