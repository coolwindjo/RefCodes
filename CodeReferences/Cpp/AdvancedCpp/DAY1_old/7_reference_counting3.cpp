#include <iostream>
#include <vector>

class Car
{
	int speed;
	int refCount = 0;
public:
	void AddRef() { ++refCount; }

	void Release() { if (--refCount == 0) delete this; }

	// protected �Ҹ��� : ��ü�� ���ÿ� ����� ���� �Ҷ� ����ϴ� ���
protected:
	~Car() { std::cout << "~Car" << std::endl; }

	// ���� ����� ���� �Ϸ��� ��� �ұ� ?
	//void* operator new(size_t sz) { return nullptr;  
	void* operator new(size_t sz)
	{
//		static_assert(false, "can't new ..");
		return nullptr;				// C++ IDioms ����Ʈ 71 �� ���.
	}
};

int main()
{
	// ���ÿ� ����� ���� �غ���.
//	Car c; // ��ü �ı��� �Ҹ��ڸ� ȣ���ؾ� �ϴµ�, �Ҹ��ڰ� protected�� �����Ƿ� error
			// �ᱹ ���ÿ� �����Ҽ� ����.

	Car* p1 = new Car;
	p1->AddRef();	

	Car* p2 = p1;
	p2->AddRef();	

	p2->Release();  
	p1->Release();  
}




