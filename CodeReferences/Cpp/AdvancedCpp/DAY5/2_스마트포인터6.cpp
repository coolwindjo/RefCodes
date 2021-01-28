#include <iostream>

class Car
{
public:
	void Go() { std::cout << "Go" << std::endl; }
	~Car() { std::cout << "~Car" << std::endl; }
};

// C++ 표준 스마트포인터를 사용하려면
#include <memory>

int main()
{
	std::shared_ptr<Car> sp1(new Car); // 참조계수로 관리.
	std::shared_ptr<Car> sp2 = sp1; // 이순간 참조계수 증가

	// 1. 크기
	std::cout << sizeof(sp1) << std::endl; // 8 (32비트 환경)

	// 2. .과 -> 연산자

	// -> : 대상체(Car) 의 멤버 접근
	sp1->Go();

	// . : shared_ptr 자체의 함수 사용.
	int cnt = sp1.use_count(); // 현재 참조계수의 카운트.. 2
	sp1.reset(); // sp1 = nullptr 의 의미.
}



// 오전 소스는 카페에 있습니다.