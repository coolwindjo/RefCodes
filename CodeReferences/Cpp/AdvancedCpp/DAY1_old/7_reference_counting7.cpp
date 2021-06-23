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

template<typename T> class RefCount
{
	mutable int refCount = 0; // mutable  멤버 데이타 : 상수 멤버 함수에서도 값 변경 가능.
public:
	// 상수 객체라도 수명 관리는 되어야 합니다.
	// 참조 계수를 관리하는 함수는 반드시 "상수 멤버 함수" 가 되어야 합니다.
	void AddRef() const { ++refCount; }



	//void Release()     // void Release( RefCount* this )
	void Release() const // void Release( const RefCount* this )
	{
		// 멤버변수 = 10; // this->멤버변수 = 10 에서 this는 상수를 가리키므로 error

		if (--refCount == 0)
			//	delete static_cast<T*>(this); // static_cast<Truck*>( const RefCount* this)
			//	delete static_cast<T*>( const_cast<RefCount*>(this) ); // ok

			//	delete const_cast<T*>(static_cast<const T*>(this));		// ok
								// const_cast<Truck*>( static_cast< const Truck*> ( const RefCount* this)
			delete static_cast<const T*>(this);
				// delete static_cast<const Truck*>(const RefCount* this)
	}

	// github.com/aosp-mirror   : 안드로이드 오픈소스
	// platform_system_core 레포지토리 검색
	// libutils/include/utils/LightRefbase.h 열어 보세요.  - DecStrong() 함수 찾으세요..
	//													delete 모양 보세요..

	// github.com/webkit
	// webkit/source/wtf/wtf/RefCounted.h 
	// deref 함수를 확인해 보세요



protected:
	~RefCount() { std::cout << "~RefCount" << std::endl; }
};

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






