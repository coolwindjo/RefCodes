#include <vector>
#include <iostream>

// ����� ���� allocator
template<typename T> class MyAlloc
{
public:
	// ��ӵ� 4���� �Լ�
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
	void destroy(T* p)  // �Ҹ��ڸ� ȣ���ϱ� ���� �Լ�
	{
		p->~T();  // �Ǵ� std::destroy_at(p);
	}
	// �����ڸ� ȣ���ϴ� �Լ���.. ������ ���ڱ��� �޾ƾ� �մϴ�.
	// �Ϻ��� ������ ����� �ʿ��մϴ�.
	template<typename U, typename ... ARGS>
	void construct(U* addr, ARGS&& ... args)
	{
		new(addr) U( std::forward<ARGS>(args)... ); 
	}
	
	// 4���� �Լ� ���� �䱸������ ���� �ֽ��ϴ�.
	typedef T value_type;
	MyAlloc() = default;		// ����Ʈ ������
	template<typename U> MyAlloc(const MyAlloc<U>& ) {}	// ���ø� ������..
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

