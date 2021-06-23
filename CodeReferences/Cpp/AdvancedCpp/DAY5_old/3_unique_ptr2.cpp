#include <iostream>

// �̹� �ܰ��� �ٽ� : "������ ����"

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
	// ����..!!! ���� void* ���·� delete �ϸ� �ȵ˴ϴ�.
	//inline void operator()(void* p) noexcept
	inline void operator()(T* p) noexcept
	{
		std::cout << "delete" << std::endl;
		delete p;
	}
};

template<typename T, typename D = default_delete<T> > class unique_ptr
{
	T* obj;
public:
	inline explicit unique_ptr(T* p = 0) : obj(p) {}

	inline ~unique_ptr() 
	{
		D d;    // �����Ҷ� ����� ��ü
		d(obj); // �ڿ� ���� - d.operator()(obj)
	}

	inline T* operator->() { return obj; }
	inline T& operator*() { return *obj; }

	unique_ptr(const unique_ptr&) = delete;
	void operator=(const unique_ptr&) = delete;
};

int main()
{	
	// �����ڸ� �����Ҽ� �ְ� �ؾ� �Ѵ�.
	// ��� 1. ������ ���ڷ� �Լ��� ��������.
	//			=> ���������� �������Լ��� �ּҸ� �����ߴٰ�, unique_ptr �Ҹ��ڿ��� ����ؾ� �Ѵ�.

	// unique_ptr<int> p1( (int*) malloc(100), free );


	// ��� 2. ���ø� ���ڷ� �����Ҷ� ����� �Լ���ü�� ��������.
	//		=> ������ ��������� ��� �ȴ�. - �׷��� C++�� ������ ���
	unique_ptr<int, Freer > p2((int*)malloc(100));
	unique_ptr<int>         p3(new int);


	// shared_ptr vs unique_ptr�� ������ ���� ���
	// => �����ڸ� �����ص� ���� Ÿ��.
//	std::shared_ptr<int> sp1(new int);
//	std::shared_ptr<int> sp2((int*)malloc(100), free));

	// => �����ڸ� �����ϸ� �ٸ� Ÿ���̴�.
//	std::unique_ptr<int> up1(new int);
//	std::unique_ptr<int, Freer> up2((int*)malloc(100)));

}


