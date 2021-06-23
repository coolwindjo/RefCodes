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

class RefCount
{
	int refCount = 0;
public:
	void AddRef() { ++refCount; }
	void Release() { if (--refCount == 0) delete this; }
protected:
	virtual ~RefCount() { std::cout << "~RefCount" << std::endl; }
};

class Truck : public RefCount 
{
public:
	~Truck() { std::cout << "~Truck" << std::endl; }
};

int main()
{
	// Truck 도 AutoPtr로 관리하고 싶습니다.
	AutoPtr<Truck> p = new Truck;
}






