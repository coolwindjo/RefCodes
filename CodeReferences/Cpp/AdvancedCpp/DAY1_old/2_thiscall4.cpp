#include <iostream>

// 가상함수의 멤버 함수 포인터

class Shape
{
public:
	virtual void Draw() const = 0; // 순수 가상 함수 : 구현이 없다.
									// 코드 메모리에 함수가 없다
};
class Rect : public Shape
{
public:
	void Draw() const override { std::cout << "Draw Rect" << std::endl; }
};
class Circle : public Shape
{
public:
	void Draw() const override { std::cout << "Draw Circle" << std::endl; }
};

int main()
{
	// f는 진짜 함수의 주소가 아니라 "가상함수테이블"의 인덱스 정보
	// Draw는 Shape 클래스의 1번째 가상함수 이므로 => "1"이라는 정보
	void(Shape::*f)() const = &Shape::Draw; // ???

	Rect r;
	(r.*f)(); // r.Draw()

	Circle c;
	(c.*f)(); // c.Draw()
}