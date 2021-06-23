#include "cppmaster.h"
//using namespace std;

class Data
{
public:
	Data() = default;
	Data(const Data& d) { LOG_FUNCTION_NAME(); }
	Data& operator=(const Data&) { LOG_FUNCTION_NAME(); return *this; }
	Data(Data&& d) { LOG_FUNCTION_NAME(); }
	Data& operator=(Data&&) { LOG_FUNCTION_NAME(); return *this; }
};

// 핵심 1. 템플릿 만들때  "T&" 로 할지  "T&&" 로 할지 잘 판단하세요
// T&  : lvalue 만 받겠다.
// T&& : lvalue 와 rvalue를 모두 받겠다는것  

// std::move() 함수를 직접 만들어 봅시다.
/*
template<typename T> T&& move(T& obj)
{
	return static_cast<T&&>(obj);
}
*/

// 인자가 T&& 일때
// lvalue(d1)을 전달하면 T 는 "Data&" 가 된다는 점이 아주 중요합니다.
// static_cast<T&&>(obj) => static_cast<Data& &&>(obj) => static_cast<Data&>(obj)

template<typename T> std::remove_reference_t<T>&& move(T&& obj)
{
	// 아래 캐스팅은 "lvalue 가 move에 도착하면 lvalue로 캐스팅"
	//               "rvalue 가 move에 도착하면 rvalue로 캐스팅"
	//return static_cast<T&&>(obj);
	// 아래 캐스팅은 무조건 "rvalue" 로 캐스팅하는 코드입니다.
	return static_cast<std::remove_reference_t<T>&&>(obj);
}
template<typename T> 
//std::conditional_t< std::is_nothrow_move_constructible_v<T> , T&&, const T&> 
std::conditional_t< !std::is_nothrow_move_constructible_v<T> && std::is_copy_constructible_v<T>, const T&, T&&>
move_if_noexcept(T& obj)
{
	return move(obj); // 위에서 만든 move 다시 호출.
					  // 결국 Data&&  타입으로 반환값이 오게 된다
}

int main()
{
	Data d1;
	Data d2 = d1;				// 복사
	Data d3 = std::move(d1);	// move 
	Data d4 = move(d1);			// move 		

	Data d5 = move(  Data() ); // 되어야 할까요 ? 안되야 할까요 ?

	Data d6 = move_if_noexcept( d2 );
				// if ( d2 의 move 생성자가 예외가 없으면 )
				//    static_cast<Data&&>(d2);		// move 생성자 호출
				// else 
				//    static_cast<const Data&>(d2); // 복사 생성자 호출
}






