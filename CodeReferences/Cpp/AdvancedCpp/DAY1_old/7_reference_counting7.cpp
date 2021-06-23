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

template<typename T> class RefCount
{
	mutable int refCount = 0; // mutable  ��� ����Ÿ : ��� ��� �Լ������� �� ���� ����.
public:
	// ��� ��ü�� ���� ������ �Ǿ�� �մϴ�.
	// ���� ����� �����ϴ� �Լ��� �ݵ�� "��� ��� �Լ�" �� �Ǿ�� �մϴ�.
	void AddRef() const { ++refCount; }



	//void Release()     // void Release( RefCount* this )
	void Release() const // void Release( const RefCount* this )
	{
		// ������� = 10; // this->������� = 10 ���� this�� ����� ����Ű�Ƿ� error

		if (--refCount == 0)
			//	delete static_cast<T*>(this); // static_cast<Truck*>( const RefCount* this)
			//	delete static_cast<T*>( const_cast<RefCount*>(this) ); // ok

			//	delete const_cast<T*>(static_cast<const T*>(this));		// ok
								// const_cast<Truck*>( static_cast< const Truck*> ( const RefCount* this)
			delete static_cast<const T*>(this);
				// delete static_cast<const Truck*>(const RefCount* this)
	}

	// github.com/aosp-mirror   : �ȵ���̵� ���¼ҽ�
	// platform_system_core �������丮 �˻�
	// libutils/include/utils/LightRefbase.h ���� ������.  - DecStrong() �Լ� ã������..
	//													delete ��� ������..

	// github.com/webkit
	// webkit/source/wtf/wtf/RefCounted.h 
	// deref �Լ��� Ȯ���� ������



protected:
	~RefCount() { std::cout << "~RefCount" << std::endl; }
};

class Truck : public RefCount<Truck>
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






