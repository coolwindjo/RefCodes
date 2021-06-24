#include <iostream>
#include <vector>

class Car
{
	int speed;
	int refCount = 0;
public:
	void AddRef() { ++refCount; }

	void Release() { if (--refCount == 0) delete this; }

	~Car() { std::cout << "~Car" << std::endl; }
};

int main()
{
	Car* p1 = new Car;
	p1->AddRef();	// 규칙 1.객체를 만들면 refCount 증가
	Car* p2 = p1;
	p2->AddRef();	// 규칙 2.객체의 주소를 복사하면 refCount 증가

	p2->Release();	// 규칙 3. 사용후 참조 개수 감소
	std::cout << "--------" <<std::endl;
	p1->Release();	// 이 순간 refCount가 0이 되므로 객체 파괴
}