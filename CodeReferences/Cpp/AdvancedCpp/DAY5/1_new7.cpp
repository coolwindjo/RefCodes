#include <vector>
#include <iostream>

// 사용자 정의 allocator
template<typename T> class MyAlloc
{
public:
	// 약속된 4개의 함수
	T* allocate(std::size_t sz)
	{
		std::cout << sz << " 개의 메모리 할당" << std::endl;
		return static_cast<T*>(malloc(sizeof(T)*sz));
	}
	void deallocate(T* addr, std::size_t sz)
	{
		std::cout << sz << " 개의 메모리 해지" << std::endl;
		free(addr);
	}
	void destroy(T* p)  // 소멸자를 호출하기 위한 함수
	{
		p->~T();  // 또는 std::destroy_at(p);
	}
	// 생성자를 호출하는 함수는.. 생성자 인자까지 받아야 합니다.
	// 완벽한 전달자 기술이 필요합니다.
	template<typename U, typename ... ARGS>
	void construct(U* addr, ARGS&& ... args)
	{
		new(addr) U( std::forward<ARGS>(args)... ); 
	}
	
	// 4개의 함수 말고도 요구사항이 좀더 있습니다.
	typedef T value_type;
	MyAlloc() = default;		// 디폴트 생성자
	template<typename U> MyAlloc(const MyAlloc<U>& ) {}	// 템플릿 생성자..
};

int main()
{
	std::vector<int, MyAlloc<int> > v;

	std::cout << "-------------" << std::endl;
	v.resize(10);
	//v.resize(20);
	v.resize(5);
	std::cout << "-------------" << std::endl;
}

