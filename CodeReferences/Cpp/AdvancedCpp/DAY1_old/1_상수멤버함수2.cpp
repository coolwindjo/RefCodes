// 핵심 : 상수 멤버 함수는 선택이 아닌 필수 문법입니다.
// 객체의 상태를 변경하지 않은 모든 멤버 함수는 반드시 "const 멤버 함수"로 해야 합니다.
// getter 는 const 멤버 함수 이어야 합니다.

class Rect
{
	int x, y, w, h;
public:
	Rect(int x, int y, int w, int h) : x{ x }, y{ y }, w{ w }, h{ h } {}

	int getArea() const { return w * h; }
};

//void foo(Rect r) // call by value : 복사본 생성
void foo(const Rect& r)
{
	int n = r.getArea(); // ??? error
}
int main()
{
	Rect r(1,2,3,4);	
	int n = r.getArea(); // ok. 
	foo(r);
}