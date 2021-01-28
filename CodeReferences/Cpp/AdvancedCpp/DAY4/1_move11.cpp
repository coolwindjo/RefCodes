#include <iostream>
#include <string>
#include <vector>
#include "cppmaster.h"

class Data
{
public:
	Data() = default;
	Data(const Data& d) { LOG_FUNCTION_NAME(); }
	Data& operator=(const Data&) { LOG_FUNCTION_NAME(); return *this; }
	Data(Data&& d) { LOG_FUNCTION_NAME(); }
	Data& operator=(Data&&) { LOG_FUNCTION_NAME(); return *this; }
};
// 핵심 : move를 지원하는 setter 만들기.
class Test
{
	Data data;
public:
	// call by value - 복사본생성으로 좋지 않다.
	// void setData(Data d) { data = d; }

	// 1. const & 사용 - C++98에서 가장 중요했던 기술
	//void setData(const Data& d) { data = d; }				// 무조건 복사
	//void setData(const Data& d) { data = std::move(d);	}	// 무조건 복사 - const 이므로

	// 방법 1. 2개의 setter
	//void setData(const Data& d) { data = d; }
	//void setData(Data&& d)      { data = std::move(d); }

	// 방법 2. call by value 는 정말 오버헤드가 클까 ?
	// move 계열 함수가 충분히 빠른 타입이면, call by value 도 나쁘지 않다.
	// 방법1 보다 느리긴 하지만 "한개의 함수"로 move를 지원할수 있데 된다.
	// void setData(Data d) { data = std::move(d); }


	// 방법 3. "방법1"의 2개의 함수를 자동생성할수 없을까 ? - "forwarding reference"
	
	// lvalue(d)			 => setData(U& d)
	// rvalue(std::move(d))  => setData(U&& d)
	template<typename U> void setData(U&& d)
	{
		// 다음중 맞는것은 ?
		//data = d;			// 무조건 복사
		//data = std::move(d);// 무조건 이동

		// 여기서 필요한건.. 인자로 lvalue가 오면 복사가 호출되도록 lvalue 캐스팅...
		// 인자로 rvalue가 오면 move가 호출되도록 rvalue 캐스팅...
		// data = static_cast<U&&>(d);
		data = std::forward<U>(d);
	}
};

int main()
{
	Data d;

	Test test;

	test.setData(d); // 복사대입 1회 호출.
					 // 복사생성 1회, move 대입 1회

	test.setData(std::move(d)); // move 대입 1회
								// move 생성 1회, move대입 1회
				// static_cast<Data&&>(d);
}








