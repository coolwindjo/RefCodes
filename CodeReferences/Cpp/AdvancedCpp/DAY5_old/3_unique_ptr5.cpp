#include <iostream>

// 이번 단계의 핵심 : unique_ptr 의 크기.

#include "PAIR.h"   //  어제 만든 compressed pair 소스

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

template<typename T, typename D = default_delete<T> > class unique_ptr
{
//	T* obj;
//	D  del; 
	PAIR<D, T*> mPair;
public:
//	inline explicit unique_ptr(T* p = 0, const D& d = D()) : obj(p), del(d) {}

	template<typename Dx = D>
	inline explicit unique_ptr(T* p = 0, Dx&& d = Dx())
									: mPair(std::forward<Dx>(d), p) {}

	inline ~unique_ptr()
	{
		//del(obj);
		mPair.getFirst()(mPair.getSecond());
	}
	 
	inline T* operator->() { return mPair.getSecond(); }
	inline T& operator*() { return *(mPair.getSecond()); }


	unique_ptr(const unique_ptr&) = delete;
	void operator=(const unique_ptr&) = delete;
};

int main()
{
	unique_ptr<int> p1(new int); 

	std::cout << sizeof(p1) << std::endl;
}


