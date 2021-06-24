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

class RefCount
{
	int refCount = 0;
public:
	void AddRef() { ++refCount; }
	void Release() { if (--refCount == 0) delete this; }

protected:
	virtual 	// Base class가 virtual destructor를 가지고 있어야 둘다 불린다.
	~RefCount() { std::cout << "~RefCount" << std::endl; }
};

class Truck	: public RefCount
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