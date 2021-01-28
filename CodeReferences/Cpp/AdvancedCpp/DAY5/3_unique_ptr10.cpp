#include <iostream>

template<typename T> struct default_delete
{
	inline void operator()(T* p) noexcept
	{
		std::cout << "delete" << std::endl;
		delete p;
	}
};

class Animal {};
class Dog : public Animal {};

void f1(int* p)    { delete p; }
void f2(Animal* p) { delete p; }

// foo �� ���ڷ� Dog�� �����ϴ� ������ �ʿ� �մϴ�.
void foo(default_delete<Dog> f)
{
	Dog* p = new Dog;
	f(p);
}

int main()
{
	// �Ʒ� �ڵ忡�� ������ ?
	int*    p1 = new int;    f1(p1); // ok
//	double* p2 = new double; f1(p2); // error

	Animal* p3 = new Animal; f2(p3); // ok
	Dog*    p4 = new Dog;    f2(p3); // ok.. ��, Animal �� �����ϴ� ������ 
									 // Dog�� ���� �Ҽ� �ִ�

	default_delete<Dog>    d1; foo(d1); // ok.. �翬�մϴ�.
	default_delete<Animal> d2; foo(d2); // ????? �Ǿ��ұ�� ? �ȵǾ� �ұ�� ?
								// �̷� ������ "������" �̶�� �մϴ�.
}








