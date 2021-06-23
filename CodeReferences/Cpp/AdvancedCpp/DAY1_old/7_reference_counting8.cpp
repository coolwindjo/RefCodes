#include <iostream>
#include <vector>


template<typename T> class AutoPtr
{
	T* obj;
public:
	AutoPtr(T* p = nullptr) : obj(p) { if (obj) obj->AddRef(); }
	AutoPtr(const AutoPtr& ap) : obj(ap.obj) { if (obj) obj->AddRef(); }
	~AutoPtr() { if (obj) obj->Release(); }

	T* operator->() { return obj; }
	T& operator*() { return *obj; }
};

// 템플릿 만들때 T에 의존하지 않은 모든 멤버 함수는
// 템플릿 이 아닌 기반 클래스를 만들어서 제공하자.

// "thin template" 또는 "template hoisting" 이라는 이름을 가진 기술
// webkit 코드 다시 보세요..
class RefCountBase
{
protected:
	mutable int refCount = 0; 
public:
	void AddRef() const { ++refCount; }
};

template<typename T> class RefCount : public RefCountBase
{
public:
	void Release() const 
	{
		if (--refCount == 0)
			delete static_cast<const T*>(this);
	}
};

class Car : public RefCount<Car> {};

class Truck : public RefCount<Truck>
{
public:
	~Truck() { std::cout << "~Truck" << std::endl; }
};

int main()
{
	const Truck* p = new Truck;

	p->AddRef();  // 호출할수 없어야 할까요 ? 있어야 할까요 ?
	p->Release();
}






