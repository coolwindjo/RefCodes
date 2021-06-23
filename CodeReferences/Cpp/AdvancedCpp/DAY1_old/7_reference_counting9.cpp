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

class RefCountBase
{
protected:
	mutable int refCount = 0;
public:
	void AddRef() const { ++refCount; }
};

// std::default_delete<T> : C++ ǥ���� �����ϴ� ������ �Լ� ��ü.
//						() ������ �ȿ��� delete �ϰ� �ֽ��ϴ�.
// webkit �� ���� ���� ������..
template<typename T, typename Deleter = std::default_delete<T> > class RefCount : public RefCountBase
{
public:
	void Release() const
	{
		// �Ʒ� �ڵ�� ��ü �ı��� ������ delete �ϰ� �ֽ��ϴ�. 
		// ��� ��ü�� new�� ������ �Ѵٴ� ���� ������ ������ �ִٴ� �ǹ�.!
		//if (--refCount == 0)
		//	delete static_cast<const T*>(this);

		if (--refCount == 0)
		{
			// delete �ּ�;  �ּҰ� const�� ����Ű�� �����Ͷ� ok.
			// ������(�ּ�); �������� ���¿� ���� const �� ����Ű�� �����Ͱ� �ȵɼ��� �ִ�.
			//				 �ǵ����̸� ���� ����� const�� ����Ű�� �ʰ� �ϴ°� �����ϴ�.

			Deleter d; // ���� ����� ���� ������ �Լ� ��ü
			d( const_cast<T*>(static_cast<const T*>(this)) );
			//  const Truck* 
		}
	}
};
//-----------------------------------------
template<typename T> struct MyDeleter
{
	void operator()(T* p) const
	{
		std::cout << "My Deleter" << std::endl;
		delete p;
	}
};


//class Truck : public RefCount<Truck, MyDeleter<Truck> >
class Truck : public RefCount<Truck>  // default_delete �� ������..
{
public:
	~Truck() { std::cout << "~Truck" << std::endl; }
};

int main()
{
	const Truck* p = new Truck;

	p->AddRef();  // ȣ���Ҽ� ����� �ұ�� ? �־�� �ұ�� ?
	p->Release();
}



// modern C++ => C++20


// ���� �ҽ��� ī�信 ���� �ø� �ڽ��ϴ�...