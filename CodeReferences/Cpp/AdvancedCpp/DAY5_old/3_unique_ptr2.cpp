#include <iostream>

// 이번 단계의 핵심 : "삭제자 변경"

struct Freer
{
	inline void operator()(void* p) noexcept
	{
		std::cout << "free" << std::endl;
		free(p);
	}
};
template<typename T> struct default_delete
{
	// 주의..!!! 절대 void* 상태로 delete 하면 안됩니다.
	//inline void operator()(void* p) noexcept
	inline void operator()(T* p) noexcept
	{
		std::cout << "delete" << std::endl;
		delete p;
	}
};

template<typename T, typename D = default_delete<T> > class unique_ptr
{
	T* obj;
public:
	inline explicit unique_ptr(T* p = 0) : obj(p) {}

	inline ~unique_ptr() 
	{
		D d;    // 삭제할때 사용할 객체
		d(obj); // 자원 삭제 - d.operator()(obj)
	}

	inline T* operator->() { return obj; }
	inline T& operator*() { return *obj; }

	unique_ptr(const unique_ptr&) = delete;
	void operator=(const unique_ptr&) = delete;
};

int main()
{	
	// 삭제자를 변경할수 있게 해야 한다.
	// 방법 1. 생성자 인자로 함수를 전달하자.
	//			=> 내부적으로 삭제자함수의 주소를 보관했다가, unique_ptr 소멸자에서 사용해야 한다.

	// unique_ptr<int> p1( (int*) malloc(100), free );


	// 방법 2. 템플릿 인자로 삭제할때 사용할 함수객체를 전달하자.
	//		=> 별도의 저장공간이 없어도 된다. - 그래서 C++이 선택한 방식
	unique_ptr<int, Freer > p2((int*)malloc(100));
	unique_ptr<int>         p3(new int);


	// shared_ptr vs unique_ptr의 삭제자 변경 방식
	// => 삭제자를 변경해도 같은 타입.
//	std::shared_ptr<int> sp1(new int);
//	std::shared_ptr<int> sp2((int*)malloc(100), free));

	// => 삭제자를 변경하면 다른 타입이다.
//	std::unique_ptr<int> up1(new int);
//	std::unique_ptr<int, Freer> up2((int*)malloc(100)));

}


