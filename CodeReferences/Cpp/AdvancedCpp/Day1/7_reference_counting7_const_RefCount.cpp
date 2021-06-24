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

template<typename T>
class RefCount
{
	mutable int refCount = 0;	// mutable Member Attributre: Constant Member Function에서도 값 변경 가능
public:
	// 상수 객체라도 수명 관리는 되어야 한다.
	// Reference Count를 관리하는 함수는 반드시 "Constant Member Function" 이 되어야 한다.
	void AddRef() const
	{ ++refCount; }

	/*/
	void Release()  		// void Release( RefCount* this )
	/*/
	void Release() const 	// void Release( const RefCount* this )
	//*/
	{
		// MemberAttribute = 10;	// Error: this->MemeberAttribute = 10
									// this가 상수를 가리키므로 Error
		if (--refCount == 0)
		/*/
			delete static_cast<T*>(this);	// static_cast<Truck*>( const RefCount* this )
		/*/
#if 0
			delete static_cast<T*>( const_cast<RefCount*>(this) );	// OK
#else
	#if 0
			delete const_cast<T*>( static_cast<const T*>(this) );	// WebKit style
				// const_cast<Truck*>( static_cast<const Truck*>(const RefCode* this) )
	#else
			delete static_cast<const T*>(this);	// Android style
				// static_cast<const Truck*>(const RefCode* this) 
	#endif
#endif
		//*/
		// https://github.com/aosp-mirror : Android open source
		// platform_system_core Repository 검색
		// libutils/include/utils/LightRefBase.h : decStrong() Search!

		// https://github.com/webkit : WekKit
		// Source/WTF/wtf/RefCounted.h : deref() Search!
	}

protected:
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
	const Truck* p = new Truck;
	p->AddRef();		// 호출 할 수 있어야 할까?
	p->Release();

	return 0;
}