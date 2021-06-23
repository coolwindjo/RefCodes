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
	Ax  ax; // 메모리 할당기
public:
	vector(int sz, const T& value = T()) : size(sz), capacity(sz)
	{
		buff = ax.allocate(size);

		int cnt = 0;
		try
		{
			for (int i = 0; i < size; i++)
			{
				//ax.construct(&buff[i], value); 
				std::allocator_traits<Ax>::construct(ax, &buff[i], value);

				++cnt;
			}
		}
		catch (...)
		{
			for (int i = 0; i < cnt; i++)
				//	ax.destroy(&buff[i]);
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
};

int main()
{
	vector<Point> v(10, Point(0, 0));



}