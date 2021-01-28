#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
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
	// 결론.. 현재 코드에서의 setter 는 2개의 setter를 제공하는것이 여러 관점에서 
	// 좋습니다.

	// 템플릿은 "다른 경우 필요할때가 있습니다."

	// 2개의 setter vs "U&&" 의 차이점.
//	void setData(const Data& d) { data = d; }
//	void setData(Data&& d)      { data = std::move(d); }

	// 이 경우의 forwarding reference 의 단점 
	//    : Data 타입에 대해서만 2개가 생성되는 것이 아니라,, 
	//		모든 타입에 대해서 setData가 생성되고 있다.
	// is_same_v<Data&, Data> => 같은 타입으로 하고싶다.
	// is_same_v<const Data, Data> => 같은 타입으로 하고싶다.
	// std::decay_t<U> => const와 reference를 제거한 타입 구하기
	// std::remove_cref_t<U> => C++20부터는 이렇게 사용. 

	template<typename U> 
	std::enable_if_t< std::is_same_v< std::decay_t<U>, Data> > 
	setData(U&& d)
	{
		data = std::forward<U>(d);
	}

	void setData(double d) { std::cout << "double" << std::endl; }
};

int main()
{
	Data d;
	Test test;
	test.setData(d); // 이순간 U의 타입은 ?
					// 1. Data   2. Data& => 답은 2
					// is_same_v<Data&, Data>   ===> false 이므로 setData의 템플릿버전
					//									사용안됨.

					// f4(n)  => T : int&

	test.setData(std::move(d)); 
	test.setData(3.4f);
}





// 오전 소스는 카페에 올려 놓았습니다.


