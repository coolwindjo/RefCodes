#include <iostream>

// 1. template ���� ������ �Ѵ�.
// 2. ���� ���� ������ �ذ��ؾ� �Ѵ�.
//   A. ���� ���� => ����Ʈ�����Ϳ����� ���� ��� �ȵ�
//   B. ���� ��� => ���� �θ� ���
//   C. ���� ���� => ���� �θ� ���
template<typename T> class Ptr
{
	T* obj;
public:
	Ptr(T* p = 0) : obj(p) {}
	~Ptr() { delete obj; }

	T* operator->() { return obj; }
	T& operator*() { return *obj; }
};

int main()
{
	Ptr<int> p1 = new int;
	*p1 = 10;
	std::cout << *p1 << std::endl;

	Ptr<int> p2 = p1; // runtime error

}


