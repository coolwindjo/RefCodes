// 아래 코드는 왜 에러일까요 ?
/*
class A
{
	int data;
public:
	void foo() { *data = 10; } 
};

int main()
{
	A a;
}
*/

// 핵심 : 클래스 템플릿에 있는 멤버 함수중.. 사용한 함수만 실제 C++ 코드로 생성됩니다.
//        "지연된 인스턴스화"라는 개념..
template<typename T> class A
{
	T data;
public:
	void foo() { *data = 10; }
};

int main()
{
	A<int> a;

	a.foo();
}








