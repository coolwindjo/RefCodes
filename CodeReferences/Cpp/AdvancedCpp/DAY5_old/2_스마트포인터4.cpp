#include <iostream>

class Animal {};
class Dog : public Animal {};


template<typename T> class Ptr
{
	T* obj;
	int* ref;   
public:
	Ptr(T* p = 0) : obj(p)
	{
		ref = new int(1);
	}
	
	Ptr(const Ptr& p) : obj(p.obj), ref(p.ref)
	{
		++(*ref);
	}
	~Ptr()
	{
		if (--(*ref) == 0)
		{
			delete obj;
			delete ref;
		}
	}
	T* operator->() { return obj; }
	T& operator*() { return *obj; }


	// Dog* 가 Animal* 로 변환 가능하다면
	// Ptr<Dog> 는 Ptr<Animal> 로 변환 가능해야 합니다.
	//Ptr(const Ptr<T>& p) {} // Ptr<Animal> 객체는 Ptr<Animal> 타입만 받을수 있다.
	//Ptr(const Ptr<Dog>& p) {} // Ptr<Animal> 객체는 Ptr<Dog> 를 인자로 받을수 있다.

	// template (복사)생성자, Generic (복사)생성자
	template<typename U> Ptr(const Ptr<U>& p) 
		: obj(p.obj), ref(p.ref)
	{
		++(*ref);
	}

	// 모든 Ptr은 friend 관계이어야 한다.
	template<typename U> friend class Ptr;
};

int main()
{
	Ptr<Dog> p1 = new Dog;

	Ptr<Dog> p2 = p1;    // ok.. 우리가 만든 복사 생성자 호출 - 참조계수 증가..

	Ptr<Animal> p3 = p1; // ??? 잘 생각해 보세요

	
//	Dog* p5 = new Dog;
//	Animal* p6 = p5; // ok..
}


