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
public:
	inline explicit unique_ptr(T* p = 0) : obj(p) {}

	inline ~unique_ptr()
	{
		D d;    // ����Ʈ �����ڷ� ��ü ����..
				// �׷���, ���� ǥ������ ����� Ÿ�Կ��� ����Ʈ �����ڰ� ����.
		d(obj); //
	}

	inline T* operator->() { return obj; }
	inline T& operator*() { return *obj; }

	unique_ptr(const unique_ptr&) = delete;
	void operator=(const unique_ptr&) = delete;
};

int main()
{
//	unique_ptr<int, Freer > p1((int*)malloc(100));

	// �����ڷ� ���� ǥ������ �����Ҽ� ������ ?

	// 1. ���ø� ���ڴ� Ÿ���� �ʿ� �ѵ�, ����ǥ������ ����� �ӽ� ��ü�̴�.
//	unique_ptr<int, [](int* p) { free(p); } > p1((int*)malloc(100));


	// 2. ����ǥ������ "�򰡵��� ���� ǥ����" �ڸ��� ������ ����.
//	unique_ptr<int, decltype( [](int* p) { free(p); } ) > p1((int*)malloc(100));


	// 3. �Ʒ� 2���� ���� �����ϴ�. �׷���, unique_ptr�� �Ҹ��ڿ��� ����..
	auto f = [](int* p) { free(p); };

	unique_ptr<int, decltype(f) > p1((int*)malloc(100));
}


