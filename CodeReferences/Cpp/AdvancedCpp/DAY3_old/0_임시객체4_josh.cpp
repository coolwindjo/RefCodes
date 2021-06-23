#include <iostream>

class Point
{
public:
	int x, y;

	Point(int a, int b) { std::cout << "Point()" << std::endl; }
	~Point() { std::cout << "~Point()" << std::endl; }
};

void f1(Point  pt) {}	// call by value: 복사본 생성
void f2(Point& pt) {}	// call by reference: 복사본 생성 안됨


Point pt(1, 2);

// 1. 값 Return과 참조 Return의 차이점: 지역변수는 참조 Return하면 안된다.
Point foo() 	// return by value: 임시 객체 반환
{
	return pt; 
}

Point& goo() 	// return by reference: Return하기 위한 임시객체를 만들지 말라는 표기법
{
	return pt; 
}

Point& hoo() 	// return by reference: Return하기 위한 임시객체를 만들지 말라는 표기법
{
	Point p(1, 2);
	return p; 	// bug: 절대 지역변수를 참조 Return하지 마세요! => 지역변수는 반드시 값 Return 해야함
}

Point& koo(Point& p) 	// return by reference: Return하기 위한 임시객체를 만들지 말라는 표기법
{
	return p; 	// 이 Code는 아무 문제 없습니다. 널리 사용됨.
}

int main()
{
	goo().x = 10; // OK. pt.x = 10
	// foo().x = 10; // Error. (Return 하기 위한) 임시객체이므로 

	Point p(0, 0);
	f1(p);
	f2(p);
}







