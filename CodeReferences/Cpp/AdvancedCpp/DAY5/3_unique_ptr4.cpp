#include <iostream>

// �̹� �ܰ��� �ٽ� : "������ ����"
// �Ʒ� Ŭ������ C++ ǥ���� �ƴմϴ�.
struct Freer
{
	inline void operator()(void* p) noexcept
	{
		std::cout << "free" << std::endl;
		free(p);
	}
};

// �Ʒ� Ŭ������ C++ ǥ�ؿ� �̹� �ֽ��ϴ�.
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
	T* obj;
	D  del; // �����ڸ� �����ϱ� ���� ���.
			// �� ����� ����Ʈ �����ڰ� �䱸 ���� �ʽ��ϴ�.
			// �ʱ�ȭ ����Ʈ�� �ڵ尡 �ֱ� ������ "���������"�� �䱸 �Ǵ� �ڵ��Դϴ�.
public:
	inline explicit unique_ptr(T* p = 0, D d = D() ) : obj(p), del(d) {}

	inline ~unique_ptr()
	{ 
		del(obj); // ����� �����ߴ�, ������ ��ü�� ����.
	}

	inline T* operator->() { return obj; }
	inline T& operator*() { return *obj; }

	unique_ptr(const unique_ptr&) = delete;
	void operator=(const unique_ptr&) = delete;
};

int main()
{
	// "Effective Modern C++" å���� "unique_ptr"�� �����ڷ� ����ǥ������ ����ϴ� ���
	// �̶�� ������ �ֽ��ϴ�... �Ʒ� ó�� �϶�� �����մϴ�.
	auto f = [](int* p) { free(p); };

	unique_ptr<int, decltype(f) > p1((int*)malloc(100), f);

	unique_ptr<int > p2(new int); // �� ���� default_delete �� ����ϰ� �Ǵ� ����
}


