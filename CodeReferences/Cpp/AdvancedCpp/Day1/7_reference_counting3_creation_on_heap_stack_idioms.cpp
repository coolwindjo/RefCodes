#include <iostream>
#include <vector>

class Car
{
	int speed;
	int refCount = 0;
public:
	void AddRef() { ++refCount; }

	void Release() { if (--refCount == 0) delete this; }

	/*/
	// Heap에 만들 수 없게 하려면?
	// void* operator new(size_t sz) {	static_assert(false, "Error: new is not permitted!"); }
	void* operator new(size_t sz) {	return nullptr; }
	// C++ Idioms - Requiring or Prohibiting Heap-based Objects (71)
	// https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms
	/*/
protected:	// protected destructor : 객체를 Stack에 만들 수 없게 할 때 사용하는 기술
	//*/
	~Car() { std::cout << "~Car" << std::endl; }
};

int main()
{
	/*/
	// Stack에 만들 수 없게 해보자
	Car c;	// Error: 객체 파괴시 소멸자를 호출해야 하는데, 소멸자가 protected에 있으므로 error
	Car* p1 = &c;
	/*/
	Car* p1 = new Car;
	//*/
	p1->AddRef();
	Car* p2 = p1;
	p2->AddRef();

	p2->Release();
	std::cout << "--------" <<std::endl;
	p1->Release();
}