#include <iostream>

// 가상함수의 멤버 함수 포인터

class Shape
{
public:
	virtual void Draw() const = 0;	// Pure Virtual Function : 구현이 없다.
									// Code memory에 함수가 없다.
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
	// f는 진짜 함수의 주소가 아니라, "Virtual Function Table"의 Index 정보
	// Draw는 Shape Class의 1 번째 가상함수이므로 => "1"이라는 정보
	void(Shape::*f)() const = &Shape::Draw;

	Rect r;
	(r.*f)();	// r.Draw()

	Circle c;
	(c.*f)();	// c.Draw()

	printf("%d\n", f);	// 1
}