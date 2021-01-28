#include <iostream>
#include <type_traits>

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

	// �Ʒ� ó�� ����� Ptr<int> = Ptr<Dog> �ÿ���..
	// �ϴ� C++ �Լ��� ��������.. ������ �Լ��� ������ �Ҷ� ����
	/*
	template<typename U> Ptr(const Ptr<U>& p)
		: obj(p.obj), ref(p.ref)
	{
		++(*ref);
	}
	*/

	template<typename U,
			std::enable_if_t< std::is_convertible_v< U*, T*>, int> = 0>
	Ptr(const Ptr<U>& p) : obj(p.obj), ref(p.ref)
	{
		++(*ref);
	}
	template<typename U> friend class Ptr;
};

int main()
{
	Ptr<Dog> p1 = new Dog;

	Ptr<Animal> p2 = p1;  // ok

	Ptr<int> p3 = p1; // ��� ������ ������ �ұ�� ?? 

}


