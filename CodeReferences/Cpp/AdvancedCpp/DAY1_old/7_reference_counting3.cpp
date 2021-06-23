#include <iostream>
#include <vector>

class Car
{
	int speed;
	int refCount = 0;
public:
	void AddRef() { ++refCount; }

	void Release() { if (--refCount == 0) delete this; }

	// protected 소멸자 : 객체를 스택에 만들수 없게 할때 사용하는 기술
protected:
	~Car() { std::cout << "~Car" << std::endl; }

	// 힙에 만들수 없게 하려면 어떻게 할까 ?
	//void* operator new(size_t sz) { return nullptr;  
	void* operator new(size_t sz)
	{
//		static_assert(false, "can't new ..");
		return nullptr;				// C++ IDioms 사이트 71 번 기술.
	}
};

int main()
{
	// 스택에 만들수 없게 해보자.
//	Car c; // 객체 파괴시 소멸자를 호출해야 하는데, 소멸자가 protected에 있으므로 error
			// 결국 스택에 생성할수 없다.

	Car* p1 = new Car;
	p1->AddRef();	

	Car* p2 = p1;
	p2->AddRef();	

	p2->Release();  
	p1->Release();  
}




