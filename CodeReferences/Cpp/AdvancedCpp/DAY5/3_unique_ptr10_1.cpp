#include <iostream>


class Animal {};
class Dog : public Animal {};

template<typename T> struct default_delete
{
	inline void operator()(T* p) noexcept
	{
		std::cout << "delete" << std::endl;
		delete p;
	}

	// "Coercion By Member Template" �̶�� �̸��� ���.
	// template ���� ������
	template<typename U>
	default_delete(const default_delete<U>&) {}

	default_delete() = default;
};

void foo(default_delete<Dog> f)
{
	Dog* p = new Dog;
	f(p);
}

int main()
{
	default_delete<Animal> d2; 
	foo(d2); // �� �ڵ尡 ���� ���� ����� ���ô�.
		
	// ���ڵ�� �ᱹ �Ʒ� �ڵ尡 ���� ������ �˴ϴ�.
	default_delete<Dog> d3 = d2;
}








