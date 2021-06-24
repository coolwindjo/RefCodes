#include <iostream>

// �����Լ��� ��� �Լ� ������

class Shape
{
public:
	virtual void Draw() const = 0;	// Pure Virtual Function : ������ ����.
									// Code memory�� �Լ��� ����.
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
	// f�� ��¥ �Լ��� �ּҰ� �ƴ϶�, "Virtual Function Table"�� Index ����
	// Draw�� Shape Class�� 1 ��° �����Լ��̹Ƿ� => "1"�̶�� ����
	void(Shape::*f)() const = &Shape::Draw;

	Rect r;
	(r.*f)();	// r.Draw()

	Circle c;
	(c.*f)();	// c.Draw()

	printf("%d\n", f);	// 1
}