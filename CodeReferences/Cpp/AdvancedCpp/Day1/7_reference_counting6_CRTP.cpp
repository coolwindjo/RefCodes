#include <iostream>
#include <vector>

template<typename T>
class AutoPtr
{
private:
	T* obj;
public:
	AutoPtr(T* p = nullptr) 	: obj(p) 		{if(obj) obj->AddRef();}
	AutoPtr(const AutoPtr &ap) 	: obj(ap.obj) 	{if(obj) obj->AddRef();}
	~AutoPtr() 									{if(obj) obj->Release();}

	T* operator->() {return obj;};
	T& operator*() 	{return *obj;};
};

// CRTP( Curiously Recurring Template Pattern )
// 파생 Class 만들 때 자신의 이름의 Base Class 의 Template 인자로 전달하는 기술
// 미래에 태어날 Derived Class 이름을 미리 사용할 수 있다.
template<typename T>
class RefCount
{
	int refCount = 0;
public:
	void AddRef() { ++refCount; }
	void Release() 	// void Release( RefCount* this )
	{
		if (--refCount == 0)
		/*/
			delete this;
		/*/
#if 0
			delete static_cast<Truck*>(this);
#else
			delete static_cast<T*>(this);
#endif
		//*/
	}

protected:
	// 다양한 Open source에서 아래 virtual destructor가 싫었다!
	// => 가상 함수가 있으면 "Vitual Function Table의 Overhead가 있음"
	// virtual	
	~RefCount() { std::cout << "~RefCount" << std::endl; }
};

class Truck	: public RefCount<Truck>
{
public:
	Truck(/* args */){}
	~Truck(){ std::cout << "~Truck" <<std::endl; }
};

int main()
{
	// Truck도 AutoPtr을 관리하고 싶다!
	AutoPtr<Truck> p = new Truck;

	return 0;
}