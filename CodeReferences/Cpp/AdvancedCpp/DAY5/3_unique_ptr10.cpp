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

// foo 의 인자로 Dog를 삭제하는 도구가 필요 합니다.
void foo(default_delete<Dog> f)
{
	Dog* p = new Dog;
	f(p);
}

int main()
{
	// 아래 코드에서 에러는 ?
	int*    p1 = new int;    f1(p1); // ok
//	double* p2 = new double; f1(p2); // error

	Animal* p3 = new Animal; f2(p3); // ok
	Dog*    p4 = new Dog;    f2(p3); // ok.. 즉, Animal 을 삭제하는 도구는 
									 // Dog도 삭제 할수 있다

	default_delete<Dog>    d1; foo(d1); // ok.. 당연합니다.
	default_delete<Animal> d2; foo(d2); // ????? 되야할까요 ? 안되야 할까요 ?
								// 이런 개념을 "공변성" 이라고 합니다.
}








