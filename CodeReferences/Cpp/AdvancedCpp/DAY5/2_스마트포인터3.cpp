#include <iostream>

// ������� ����� ����Ʈ������

template<typename T> class Ptr
{
	T* obj;
	int* ref;   // ��������� ����ų ������
public:
	Ptr(T* p = 0) : obj(p)
	{
		ref = new int(1);
	}

	// ������� ����� ���� ������
	Ptr(const Ptr& p)
		: obj(p.obj), ref(p.ref)
	{
		++(*ref);
	}	   
	~Ptr()
	{
		if (--(*ref) == 0)
		{
			delete obj;
			delete ref;
		}
	}

	T* operator->() { return obj; }
	T& operator*() { return *obj; }
};

int main()
{
	Ptr<int> p1 = new int;
	*p1 = 10;
	std::cout << *p1 << std::endl;

	Ptr<int> p2 = p1; 

}


