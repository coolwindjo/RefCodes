#include "cppmaster.h"

class Point
{
	int x;
	int y;
public:
	Point(int a, int b) : x(a), y(b) {}
	~Point() {}
};


template<typename T, typename Ax = std::allocator<T> > class vector
{
	T* buff;
	int size;
	int capacity;
	Ax  ax;
public:
	vector(int sz, const T& value = T()) : size(sz), capacity(sz)
	{
		buff = ax.allocate(size);

		int cnt = 0;
		try
		{
			for (int i = 0; i < size; i++)
			{
				std::allocator_traits<Ax>::construct(ax, &buff[i], value);
				++cnt;
			}
		}
		catch (...)
		{
			for (int i = 0; i < cnt; i++)
				std::allocator_traits<Ax>::destroy(ax, &buff[i]);

			ax.deallocate(buff, size);
			buff = nullptr;
		}
	}
	~vector()
	{
		if (buff)
		{
			for (int i = 0; i < size; i++)
				std::allocator_traits<Ax>::destroy(ax, &buff[i]);

			ax.deallocate(buff, size);
		}
	}
	// vector 의 resize를 만들어 봅시다.
	void resize(std::size_t newSize, const T& value = T())
	{
		if (newSize > capacity)
		{
			// 아래 코드 문제점
			// 1. 디폴트 생성자가 필요 하다.
			// 2. 생성자가 호출되므로, 각요소가 자원도 할당하게됨.
			//T* temp = new T[newSize]; 

			// 1. 항상 새로운 버퍼는 메모리만 할당해야 합니다.
			T* temp = ax.allocate(newSize);

			// 2. 기존 버퍼의 요소를 move 생성자로 이동
			for (int i = 0; i < size; i++)
			{
			//	new(&temp[i]) T(buff[i]); // 복사 생성자
			//	new(&temp[i]) T(std::move(buff[i])); // move 생성자

				std::allocator_traits<Ax>::construct(ax, &temp[i], std::move_if_noexcept(buff[i]));
			}
			// 3. 새로운 공간은 resize 인자로 전달된 객체로 초기화
			for (int i = size; i < newSize; i++)
			{
				std::allocator_traits<Ax>::construct(ax, &temp[i], value);
			}
			size = newSize;
			capacity = newSize;
		}
		else
		{
			// 크기가 줄어들때.. 소멸자의 명시적 호출을 하는 코드를 만들시면 됩니다.
			// 단, size > newSize,  capapcity> newSize 를 잘 구별해서 구현해 보세요..
		}
	}
};

int main()
{
	vector<Point> v(5, Point(0, 0));

	v.resize(10, Point(0,0) ); // 키우는 경우 초기화를 위해 객체 필요

	v.resize(3, Point(0,0));
}