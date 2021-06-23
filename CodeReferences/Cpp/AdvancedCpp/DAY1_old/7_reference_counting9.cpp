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

class RefCountBase
{
protected:
	mutable int refCount = 0;
public:
	void AddRef() const { ++refCount; }
};

// std::default_delete<T> : C++ 표준이 제공하는 삭제자 함수 객체.
//						() 연산자 안에서 delete 하고 있습니다.
// webkit 의 모양과 비교해 보세요..
template<typename T, typename Deleter = std::default_delete<T> > class RefCount : public RefCountBase
{
public:
	void Release() const
	{
		// 아래 코드는 객체 파괴를 무조건 delete 하고 있습니다. 
		// 모든 객체를 new로 만들어야 한다는 제약 조건을 가지고 있다는 의미.!
		//if (--refCount == 0)
		//	delete static_cast<const T*>(this);

		if (--refCount == 0)
		{
			// delete 주소;  주소가 const를 가리키는 포인터라도 ok.
			// 삭제자(주소); 삭제자의 형태에 따라 const 를 가리키는 포인터가 안될수도 있다.
			//				 되도록이면 최종 결과가 const를 가리키지 않게 하는게 안전하다.

			Deleter d; // 삭제 방식을 담은 삭제자 함수 객체
			d( const_cast<T*>(static_cast<const T*>(this)) );
			//  const Truck* 
		}
	}
};
//-----------------------------------------
template<typename T> struct MyDeleter
{
	void operator()(T* p) const
	{
		std::cout << "My Deleter" << std::endl;
		delete p;
	}
};


//class Truck : public RefCount<Truck, MyDeleter<Truck> >
class Truck : public RefCount<Truck>  // default_delete 로 삭제됨..
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



// modern C++ => C++20


// 오늘 소스는 카페에 지금 올리 겠습니다...