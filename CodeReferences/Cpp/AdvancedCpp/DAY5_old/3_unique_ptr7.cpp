#include <iostream>
#include "PAIR.h"   

// �̹� �ܰ��� �ٽ� : �迭 ���� ���� - ���� ���� ����...

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
	PAIR<D, T*> mPair;   // PAIR<D, int[]*> mPair  �� ����ε�..
						 //  int[]* Ÿ���� ���� ���� �ʽ��ϴ�.
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

int main()
{
	unique_ptr<int> p1(new int);

	unique_ptr<int[]> p2(new int[10]); // delete[] 

}

