// forwarding reference가 가지는 의미!!

// 방법 1. call by value
//		=> 복사본 생성. user type이면 overhead가 있다.
// void foo(int n) {}

// 방법 2. call by reference
// 		=> lvalue만 받을 수 있다.
// void foo(int& n) {}

// 방법 3. const lvalue reference
// 		=> 복사본도 없고, lvalue, rvalue 모두 받을 수 있다.
//		=> 단, 상수성이 추가된다. 읽기만 가능하고, 상수 Member함수만 호출가능	
//								"move 될 수 없다"
// void foo(const int& n) {}

// 방법 4. 상수성없이 모두 받으려면,
//			2개의 함수를 별도로 만들어라
// void foo(int&) {}
// void foo(int&&) {}

// 방법 5. "방법 4"의 2개 함수 구현이 동일하다면,
//			2개 함수를 자동 생성되게 하자.
// 			"forwarding reference"를 인자로 가지는 함수!!
template<typename T> void foo(T&& arg) {}

int main()
{
	int n = 10;

	// lvalue 와 rvalue를 모두 받을수 있는 foo 함수를 만들고 싶다
	foo(n);
	foo(10);
}
