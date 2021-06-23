#include <iostream>

// 이번 단계의 핵심 : "삭제자 변경"
// 아래 클래스는 C++ 표준은 아닙니다.
struct Freer
{
	inline void operator()(void* p) noexcept
	{
		std::cout << "free" << std::endl;
		free(p);
	}
};

// 아래 클래스는 C++ 표준에 이미 있습니다.
template<typename T> struct default_delete
{
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
		D d;    // 디폴트 생성자로 객체 생성..
				// 그런데, 람다 표현식이 만드는 타입에는 디폴트 생성자가 없다.
		d(obj); //
	}

	inline T* operator->() { return obj; }
	inline T& operator*() { return *obj; }

	unique_ptr(const unique_ptr&) = delete;
	void operator=(const unique_ptr&) = delete;
};

int main()
{
//	unique_ptr<int, Freer > p1((int*)malloc(100));

	// 삭제자로 람다 표현식을 전달할수 없을까 ?

	// 1. 템플릿 인자는 타입이 필요 한데, 람다표현식의 결과는 임시 객체이다.
//	unique_ptr<int, [](int* p) { free(p); } > p1((int*)malloc(100));


	// 2. 람다표현식은 "평가되지 않은 표현식" 자리에 넣을수 없다.
//	unique_ptr<int, decltype( [](int* p) { free(p); } ) > p1((int*)malloc(100));


	// 3. 아래 2줄은 문제 없습니다. 그런데, unique_ptr의 소멸자에서 에러..
	auto f = [](int* p) { free(p); };

	unique_ptr<int, decltype(f) > p1((int*)malloc(100));
}


