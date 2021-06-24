#include <iostream>
#include <vector>

class Car
{
	int speed;
	int refCount = 0;
public:
	void AddRef() { ++refCount; }
	void Release() { if (--refCount == 0) delete this; }

	void Go() { std::cout << "Car goes!"<<std::endl; }

protected:
	~Car() { std::cout << "~Car" << std::endl; }
};

// RefCount를 자동으로 관리해주는 Smart Pointer
template<typename T>
class AutoPtr
{
private:
	T* obj;
public:
	AutoPtr(T* p = nullptr) 	: obj(p) 		{if(obj) obj->AddRef();}
	AutoPtr(const AutoPtr &ap) 	: obj(ap.obj) 	{if(obj) obj->AddRef();}
	~AutoPtr() 									{if(obj) obj->Release();}

	// Smart Pointer의 기본: -> 와 * 연산자 재정의
	T* operator->() {return obj;};
	T& operator*() 	{return *obj;};
};

int main()
{
	AutoPtr<Car> p1 = new Car;	// AutoPtr<Car> p1(new Car);

	AutoPtr<Car> p2 = p1;

	p2->Go();

}