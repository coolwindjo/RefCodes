// 6_enable_if1.cpp

// C++11 표준에 "그대로" 있는 Code입니다.
template<bool, typename T = void > struct enable_if
{
	typedef  T type;
};

template<typename T> struct enable_if<false, T> 
{
};

int main()
{
	// 아래 코드에서 각 변수의 타입은 ?
	enable_if<true, int>::type  n1; // int n1
	enable_if<true>::type       n2; // void n2 -> Error
	enable_if<false, int>::type n3; // type 이 없으므로 Compile error 

	// 핵심
	// enable_if<true, TYPE>::type 은 "TYPE"
	// enable_if<false, TYPE>::type 은 ::type이 없다는 Error
}