#include <vector>
#include "cppmaster.h"
using namespace std;

class Data
{
public:
	Data() = default;
	Data(const Data& d) { LOG_FUNCTION_NAME(); }
	Data& operator=(const Data&) { LOG_FUNCTION_NAME(); return *this; }

	Data(Data&& d) { LOG_FUNCTION_NAME(); }
	Data& operator=(Data&&) { LOG_FUNCTION_NAME(); return *this; }
};
// 핵심 : "Const Object 는 move 될수 없다." 
//			std::move() 사용시 "복사생성자 호출"
int main()
{
	Data d1;
	Data d2 = d1;			 // 복사 생성자 호출
	Data d3 = std::move(d1); // move 생성자

	const Data d4; // 상수 객체
	Data d5 = d4;			
	Data d6 = std::move(d4); // 복사 생성자 호출. 상수객체는 move될수 없다.
				// static_cast< d4타입 &&>(d4);
				// static_cast< const Data &&>(d4);  이므로
				//				=> Data(Data&& d) 로 갈수 없다.
				//				=> Data(const Data& d) 로 갈수 있다.
}