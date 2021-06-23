// 1_new8
#include "cppmaster.h"

class Point
{
	int x;
	int y;
public:
	Point() : x(0), y(0) { LOG_FUNCTION_NAME(); }
	Point(int a, int b) : x(a), y(b) { LOG_FUNCTION_NAME(); }
	~Point() { LOG_FUNCTION_NAME(); }
};


template<typename T> class MyAlloc
{
public:
	T* allocate(std::size_t sz)
	{
		std::cout << sz << " ���� �޸� �Ҵ�" << std::endl;
		return static_cast<T*>(malloc(sizeof(T)*sz));
	}
	void deallocate(T* addr, std::size_t sz)
	{
		std::cout << sz << " ���� �޸� ����" << std::endl;
		free(addr);
	}

	typedef T value_type;
	MyAlloc() = default;		
	template<typename U> MyAlloc(const MyAlloc<U>&) {}
};


int main()
{	
	MyAlloc<Point> ax;

	Point* p1 = ax.allocate(1); 

	//ax.construct(p1, 1, 2);  
	//ax.destroy(p1);

	std::allocator_traits< MyAlloc<Point> >::construct(ax, p1, 1, 2);
									// ax �� construct �Լ��� ������ ax.construct(p1, 1,2)
									// ������ new(p1) T(1,2) ����.
	std::allocator_traits< MyAlloc<Point> >::destroy(ax, p1);

	ax.deallocate(p1, 1);

}



