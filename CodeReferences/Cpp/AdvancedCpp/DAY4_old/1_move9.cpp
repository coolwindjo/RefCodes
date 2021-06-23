#include <vector>
#include "cppmaster.h"
using namespace std;

class Data
{
public:
	Data() = default;
	Data(const Data& d)     { LOG_FUNCTION_NAME(); }
	Data& operator=(const Data&) { LOG_FUNCTION_NAME(); return *this; }

	// move 계열 함수를 만들때
	// 1. 되도록 예외가 없는 코드만 사용하세요
	// 2. 그리고, 예외가 없음을 컴파일러에게 알려주세요 - 핵심

	Data(Data&& d) noexcept          { LOG_FUNCTION_NAME(); }
	Data& operator=(Data&&) noexcept { LOG_FUNCTION_NAME(); return *this; }
};

int main()
{
	Data d1;
	Data d2 = d1; // 무조건 복사
	Data d3 = std::move(d1); // 무조건 move
	Data d4 = std::move_if_noexcept(d2); // move 생성자에 예외가 없을때만 move 생성자 사용
										 // 예외가 있으면 복사 생성자 사용

	std::vector<Data> v(5);

	cout << "-----" << endl;

	v.resize(10); // 이순간 std::move_if_noexcept 를 사용해서 이동합니다.
	
	cout << "-----" << endl;
}