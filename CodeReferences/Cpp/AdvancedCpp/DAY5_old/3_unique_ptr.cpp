// unique_ptr.cpp   - ����Ʈ������ 2�� �����ϼ���.
#include <iostream>

template<typename T> class unique_ptr
{
	T* obj;
public:
	inline explicit unique_ptr(T* p = 0) : obj(p) {}
	inline ~unique_ptr() { delete obj; }

	inline T* operator->() { return obj; }
	inline T& operator*() { return *obj; }

	// ���� �����ڿ� ���Կ����ڸ� �����Ѵ�.
	unique_ptr(const unique_ptr&) = delete;
	void operator=(const unique_ptr&) = delete;
};
int main()
{
	unique_ptr<int> p1(new int);
	*p1 = 10;
	std::cout << *p1 << std::endl;

//	unique_ptr<int> p2 = p1; // compile error

}


