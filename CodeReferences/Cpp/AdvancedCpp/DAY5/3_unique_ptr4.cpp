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
	D  del; // 삭제자를 보관하기 위한 멤버.
			// 이 모양은 디폴트 생성자가 요구 되지 않습니다.
			// 초기화 리스트에 코드가 있기 때문에 "복사생성자"가 요구 되는 코드입니다.
public:
	inline explicit unique_ptr(T* p = 0, D d = D() ) : obj(p), del(d) {}

	inline ~unique_ptr()
	{ 
		del(obj); // 멤버로 보관했던, 삭제자 객체로 삭제.
	}

	inline T* operator->() { return obj; }
	inline T& operator*() { return *obj; }

	unique_ptr(const unique_ptr&) = delete;
	void operator=(const unique_ptr&) = delete;
};

int main()
{
	// "Effective Modern C++" 책에서 "unique_ptr"의 삭제자로 람다표현식을 사용하는 방법
	// 이라는 주제가 있습니다... 아래 처럼 하라고 권장합니다.
	auto f = [](int* p) { free(p); };

	unique_ptr<int, decltype(f) > p1((int*)malloc(100), f);

	unique_ptr<int > p2(new int); // 이 경우는 default_delete 를 사용하게 되는 원리
}


