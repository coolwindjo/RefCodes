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
// CRTP ( Curiously Recurring Template Pattern )
// 파생 클래스 만들때 자신의 이름의 기반 클래스의 템플릿 인자로 전달하는 기술
// 미래에 태어날 파생 클래스 이름을 미리 사용할수 있다.
template<typename T> class RefCount
{
	int refCount = 0;
public:
	void AddRef() { ++refCount; }

	void Release()		// void Release( RefCount* this )
	{
		if (--refCount == 0)
			//	delete this; 
			delete static_cast<T*>(this); 
	}

protected:
	// 다양한 오픈소스에서 아래 소멸자의 가상함수가 싫었다.!! 
	// => 가상함수가 있으면 "가상함수 테이블의 오버헤드가 있습니다."
	//virtual ~RefCount() { std::cout << "~RefCount" << std::endl; }
	~RefCount() { std::cout << "~RefCount" << std::endl; }
};


class Truck : public RefCount<Truck>
{
public:
	~Truck() { std::cout << "~Truck" << std::endl; }
};

int main()
{
	AutoPtr<Truck> p = new Truck;
}






