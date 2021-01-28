#include <iostream>
#include "PAIR.h"   

// 이번 단계의 핵심 : 배열 버전에 다른 기능 추가

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
	inline void operator()(T* p) noexcept
	{
		std::cout << "delete" << std::endl;
		delete p;
	}
};
template<typename T> struct default_delete< T[] >
{
	inline void operator()(T* p) noexcept
	{
		std::cout << "delete[]" << std::endl;
		delete[] p;
	}
};

template<typename T, typename D = default_delete<T> > class unique_ptr
{
	PAIR<D, T*> mPair;
public:
	template<typename Dx = D>
	inline explicit unique_ptr(T* p = 0, Dx&& d = Dx())
		: mPair(std::forward<Dx>(d), p) {}

	inline ~unique_ptr()
	{
		mPair.getFirst()(mPair.getSecond());
	}

	inline T* operator->() { return mPair.getSecond(); }
	inline T& operator*() { return *(mPair.getSecond()); }

	unique_ptr(const unique_ptr&) = delete;
	void operator=(const unique_ptr&) = delete;

	unique_ptr(unique_ptr&& up) noexcept(std::is_nothrow_move_constructible_v<PAIR<D, T*>>)
		: mPair(std::move(up.mPair))
	{
		up.mPair.getSecond() = nullptr;
	}
	unique_ptr& operator=(unique_ptr&& up) noexcept(std::is_nothrow_move_assignable_v<PAIR<D, T*>>)
	{
		mPair = std::move(up.mPair);
		up.mPair.getSecond() = nullptr;
		return *this;
	}
};

template<typename T, typename D > class unique_ptr<T[], D>
{
	PAIR<D, T*> mPair;
public:
	template<typename Dx = D>
	inline explicit unique_ptr(T* p = 0, Dx&& d = Dx())
		: mPair(std::forward<Dx>(d), p) {}

	inline ~unique_ptr()
	{
		mPair.getFirst()(mPair.getSecond());
	}

	inline T* operator->() { return mPair.getSecond(); }


	// 배열 버전에서는 * 연산자 대신에 [] 연산자를 제공합니다.
	//inline T& operator*() { return *(mPair.getSecond()); }

	inline T& operator[](int idx) { return mPair.getSecond()[idx]; }



	unique_ptr(const unique_ptr&) = delete;
	void operator=(const unique_ptr&) = delete;

	unique_ptr(unique_ptr&& up) noexcept(std::is_nothrow_move_constructible_v<PAIR<D, T*>>)
		: mPair(std::move(up.mPair))
	{
		up.mPair.getSecond() = nullptr;
	}
	unique_ptr& operator=(unique_ptr&& up) noexcept(std::is_nothrow_move_assignable_v<PAIR<D, T*>>)
	{
		mPair = std::move(up.mPair);
		up.mPair.getSecond() = nullptr;
		return *this;
	}
};

// 자원의 할당과 unique_ptr의 생성을 한번에 할수 있어야 안전합니다.
// 아래 함수를 제공합니다
template<typename T, typename ... ARGS>
unique_ptr<T> make_unique(ARGS&& ... args)
{
	return unique_ptr<T>{new T{ std::forward<ARGS>(args)... } };
}

int goo() { return 0; }
void foo( unique_ptr<int> up, int n) {}

int main()
{
	// 아래 코드는 복사 생성자아니라 move 생성자로 전달하는 모양입니다.
	//foo( unique_ptr<int>(new int), goo());
	//foo( make_unique<Point>(1,2,3) , goo());
	foo(make_unique<int>(3), goo());

}








