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


	// Dog* �� Animal* �� ��ȯ �����ϴٸ�
	// Ptr<Dog> �� Ptr<Animal> �� ��ȯ �����ؾ� �մϴ�.
	//Ptr(const Ptr<T>& p) {} // Ptr<Animal> ��ü�� Ptr<Animal> Ÿ�Ը� ������ �ִ�.
	//Ptr(const Ptr<Dog>& p) {} // Ptr<Animal> ��ü�� Ptr<Dog> �� ���ڷ� ������ �ִ�.

	// template (����)������, Generic (����)������
	template<typename U> Ptr(const Ptr<U>& p) 
		: obj(p.obj), ref(p.ref)
	{
		++(*ref);
	}

	// ��� Ptr�� friend �����̾�� �Ѵ�.
	template<typename U> friend class Ptr;
};

int main()
{
	Ptr<Dog> p1 = new Dog;

	Ptr<Dog> p2 = p1;    // ok.. �츮�� ���� ���� ������ ȣ�� - ������� ����..

	Ptr<Animal> p3 = p1; // ??? �� ������ ������

	
//	Dog* p5 = new Dog;
//	Animal* p6 = p5; // ok..
}


