#include <iostream>
#include <vector>


template<typename T> class AutoPtr
{
	T* obj;
public:
	AutoPtr(T* p = nullptr) : obj(p) { if (obj) obj->AddRef(); }
	AutoPtr(const AutoPtr& ap) : obj(ap.obj) { if (obj) obj->AddRef(); }
	~AutoPtr() { if (obj) obj->Release(); }

	T* operator->() { return obj; }
	T& operator*() { return *obj; }
};
// CRTP ( Curiously Recurring Template Pattern )
// �Ļ� Ŭ���� ���鶧 �ڽ��� �̸��� ��� Ŭ������ ���ø� ���ڷ� �����ϴ� ���
// �̷��� �¾ �Ļ� Ŭ���� �̸��� �̸� ����Ҽ� �ִ�.
template<typename T> class RefCount
{
	int refCount = 0;
public:
	void AddRef() { ++refCount; }

	void Release()		// void Release( RefCount* this )
	{
		if (--refCount == 0)
			//	delete this; 
			delete static_cast<T*>(this); 
	}

protected:
	// �پ��� ���¼ҽ����� �Ʒ� �Ҹ����� �����Լ��� �Ⱦ���.!! 
	// => �����Լ��� ������ "�����Լ� ���̺��� ������尡 �ֽ��ϴ�."
	//virtual ~RefCount() { std::cout << "~RefCount" << std::endl; }
	~RefCount() { std::cout << "~RefCount" << std::endl; }
};


class Truck : public RefCount<Truck>
{
public:
	~Truck() { std::cout << "~Truck" << std::endl; }
};

int main()
{
	AutoPtr<Truck> p = new Truck;
}






