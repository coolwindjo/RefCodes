#include <iostream>
#include <vector>
#include <memory>	// std::default_delete<T>

class RefCountBase
{
protected:
	mutable int refCount = 0;
public:
	void AddRef() const
	{ ++refCount; }
};

// std::default_delete<T> : C++ 표준이 제공하는 삭제자 함수 객체
						// () 연산자 안에서 delete 실행 됨
						// Webkit source 와 비교해보자
template<typename T, typename Deleter = std::default_delete<T>>
class RefCount : public RefCountBase
{
public:
	void Release() const
	{
		// 아래 Code는 객체 파괴를 무조건 delete 하고 있습니다.
		// 모든 객체를 new로 만들어야 한다는 제약 조건을 가지고 있다는 의미...
		/*/
		if (--refCount == 0)
			delete static_cast<const T*>(this);
		/*/
		if (--refCount == 0) {
			// delete 주소: 주소가 const 를 가리키는 Pointer 라도 OK
			// Deleter(주소): 삭제자의 형태에 따라 const 를 가리키는 Pointer가 안될 수도 있다.
			//				  되도록이면 최종 결과가 const 를 가리키지 않게 하는게 안전(?, flexible)하다.
			/*/
			Deleter()(static_cast<const T*>(this));	// Error: const Truck*
			/*/
			Deleter()( const_cast<T*>(static_cast<const T*>(this)) );	// Truck*
			//*/
		}
		//*/
	}
protected:
	~RefCount() { std::cout << "~RefCount" << std::endl; }
};

//---------------------------------
template<typename T>
struct MyDeleter
{
	void operator()(T* p) const	// (const T* p) 로 받지 않는 것이 더 flexible 하다.
	{
		std::cout << "My Deleter" <<std::endl;
		delete p;
	}
};

class Truck	: public RefCount< Truck, MyDeleter<Truck> >
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