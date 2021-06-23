// 카페에서 3일차 사전소스 받으시면 됩니다.
// cafe.naver.com/cppmaster

#include <iostream>
#include <type_traits>

class Point
{
public:
	int x, y;

	Point(int a, int b)	{ std::cout << "Point()" << std::endl;	}
	~Point()            { std::cout << "~Point()" << std::endl;	}
};
// 1. 임시객체개념. 만드는 법. 수명..

int main()
{
//	Point pt(1, 2); // named object

//	Point (1, 2);	// unnamed object. 임시객체(temporary)
					// 수명 : 문장의 끝

	Point(1, 2), std::cout << "A" << std::endl;

	std::cout << "-------" << std::endl;

}






