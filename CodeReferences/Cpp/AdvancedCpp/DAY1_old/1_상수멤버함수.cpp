// VC 에서 빌드 안될때

// 프로젝트 메뉴 - 속성 메뉴 선택후

// "Windows SDK 버전"과 "플랫폼 도구집합" 버전 맞추세요..

// Mingw 압축풀고

// mingw/bin 폴더를 "Path" 환경변수에 등록해 주세요..

// Visual Studio 의 컴파일러이름.. => cl.exe
// => 시작 버튼 누르시고 => "visual studio 폴더에서"
// => 개발자 명령 프롬프트 실행하세요..

// C++20 기술을 사용하려면
// VS 2019 Preview 설치 필요
// g++10.2







// DAY1.zip 압축풀러주세요..

// 1_상수멤버함수.cpp 열어 보세요

#include <iostream>

class Point
{
public:
	int x, y;

	Point(int a, int b) : x(a), y(b) {}

	void set(int a, int b) { x = a; y = b; }

	void print() const	// 상수 멤버 함수.
	{
		//x = 10;	// error. 상수 멤버 함수 안에서는 모든 멤버는 상수	

		std::cout << x << ", " << y << std::endl;
	}
};
int main()
{
	const Point pt(1, 2);

	pt.x = 10;		// error
	pt.set(10, 20);	// error
	pt.print();		// error. 
				// 호출되게 하려면 print()는 반드시 상수 멤버 함수 이어야 합니다.

	// 핵심 : 상수 객체는 "상수 멤버 함수만 호출" 할수 있다.
}


