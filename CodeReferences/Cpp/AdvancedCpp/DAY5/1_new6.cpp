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
				ax.construct(&buff[i], value); // 할당기의 함수로 복사 생성자 호출
				++cnt;
			}
		}
		catch (...)
		{
			for (int i = 0; i < cnt; i++)
				ax.destroy(&buff[i]);
			ax.deallocate(buff, size);
			buff = nullptr;
		}
	}
	~vector()
	{
		if (buff)
		{
			for (int i = 0; i < size; i++)
				ax.destroy(&buff[i]);
			ax.deallocate(buff, size);
		}
	}
};

int main()
{
	vector<Point> v(10, Point(0, 0)); 
	
	

}