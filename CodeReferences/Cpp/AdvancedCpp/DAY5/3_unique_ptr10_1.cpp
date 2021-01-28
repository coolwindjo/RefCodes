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

	// "Coercion By Member Template" 이라는 이름의 기술.
	// template 복사 생성자
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
	foo(d2); // 이 코드가 에러 없게 만들어 봅시다.
		
	// 위코드는 결국 아래 코드가 문제 없으면 됩니다.
	default_delete<Dog> d3 = d2;
}








