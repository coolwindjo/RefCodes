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
	// vector �� resize�� ����� ���ô�.
	void resize(std::size_t newSize, const T& value = T())
	{
		if (newSize > capacity)
		{
			// �Ʒ� �ڵ� ������
			// 1. ����Ʈ �����ڰ� �ʿ� �ϴ�.
			// 2. �����ڰ� ȣ��ǹǷ�, ����Ұ� �ڿ��� �Ҵ��ϰԵ�.
			//T* temp = new T[newSize]; 

			// 1. �׻� ���ο� ���۴� �޸𸮸� �Ҵ��ؾ� �մϴ�.
			T* temp = ax.allocate(newSize);

			// 2. ���� ������ ��Ҹ� move �����ڷ� �̵�
			for (int i = 0; i < size; i++)
			{
			//	new(&temp[i]) T(buff[i]); // ���� ������
			//	new(&temp[i]) T(std::move(buff[i])); // move ������

				std::allocator_traits<Ax>::construct(ax, &temp[i], std::move_if_noexcept(buff[i]));
			}
			// 3. ���ο� ������ resize ���ڷ� ���޵� ��ü�� �ʱ�ȭ
			for (int i = size; i < newSize; i++)
			{
				std::allocator_traits<Ax>::construct(ax, &temp[i], value);
			}
			size = newSize;
			capacity = newSize;
		}
		else
		{
			// ũ�Ⱑ �پ�鶧.. �Ҹ����� ����� ȣ���� �ϴ� �ڵ带 ����ø� �˴ϴ�.
			// ��, size > newSize,  capapcity> newSize �� �� �����ؼ� ������ ������..
		}
	}
};

int main()
{
	vector<Point> v(5, Point(0, 0));

	v.resize(10, Point(0,0) ); // Ű��� ��� �ʱ�ȭ�� ���� ��ü �ʿ�

	v.resize(3, Point(0,0));
}