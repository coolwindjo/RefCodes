#include <iostream>
#include "cppmaster.h"

class Data
{
public:
	Data() = default;
	Data(const Data& d)			{ LOG_FUNCTION_NAME(); }
	Data& operator=(const Data&) { LOG_FUNCTION_NAME(); return *this; }
	Data(Data&& d)			{ LOG_FUNCTION_NAME(); }
	Data& operator=(Data&&) { LOG_FUNCTION_NAME(); return *this; }
};
//------------------------------------
// 규칙 1. 사용자가 "복사" 와 "move" 계열 함수를 모두 제공하지 않으면
//      ==> 컴파일러가 모두 제공해 준다.
//		==> 자동생성된 복사에서는 모든 멤버를 복사로 옮기고
//                     move 함수에서는 모든 멤버를 move로 옮긴다

// 규칙 2. 사용자가 "복사" 계열 함수를 제공하면
//		=> 컴파일러는 move 를 제공하지 못한다. 
//         std::move() 사용시 "사용자가 만든 복사 생성자"를 호출
//      혹시, 디폴트 버전의 move가 필요 하면 "=default" 문법으로 컴파일러에게 요청

// 규칙 3. 사용자가 "move"버전만 제공한 경우
//			===> 복사 계열 함수는 삭제 됩니다.
//				 Object(const Object& ) = delete;
//				복사 생성자를 사용할수 없다는 의미!!

class Object
{
	Data data;
	std::string name;
public:		  
	Object() {}

	/*
	Object(const Object& obj) : data(obj.data), name(obj.name) {}

	// 만약 각 함수의 디폴트 버전이 필요 하면 요청할수 있습니다.
	Object(Object&&) = default;
	Object& operator=(Object&&) = default;
	Object& operator=(const Object&) = default;
	*/
	Object(Object&& obj) : data(std::move(obj.data)), name(std::move(obj.name)) {}
};

int main()
{
	Object o1;

	Object o2 = o1;
	o2 = o1;

	Object o3 = std::move(o1);
	o3 = std::move(o2);
}