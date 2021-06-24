class Rect
{
	int x, y, w, h;
public:
	Rect(int x, int y, int w, int h) : x{ x }, y{ y }, w{ w }, h{ h } {}

	int getArea() const { return w * h; }
	// 객체의 상태를 변경하지 않는 모든 Member 함수는 반드시 "const member function"으로 만들어야 한다!
	// Getter는 const member function 이어야 한다!
};

// void foo(Rect r)	// call by value
void foo(const Rect &r)
{
	int n = r.getArea(); 
}
int main()
{
	Rect r(1,2,3,4);	
	int n = r.getArea();
	foo(r);
}