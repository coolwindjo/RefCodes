#include "cppmaster.h"

class Point
{
	int x;
	int y;
public:
	// Point �� ����Ʈ �����ڰ� �����ϴ�.
	Point(int a, int b) : x(a), y(b) {}
	~Point() {}
};

// "Generic Container Idioms"
// �����̳� ����� "Ÿ���� ������ �ϴ� ����������"
// ����Ʈ �����ڷ� �������� "���� ������"�� �䱸�ϴ� ���� ����.


template<typename T> class vector
{
	T* buff;
	int size;
	int capacity;
public:
	vector(int sz, const T& value = T() ) : size(sz), capacity(sz)
	{
		// �Ʒ� ó�� �ڵ��ϸ� T Ÿ���� �ݵ�� "����Ʈ�����ڰ� �־�� �Ѵ�" ��� ������ �ְԵ˴ϴ�
		//buff = new T[sz];

		// 1. �޸� �Ҵ�
		buff = static_cast<T*> (operator new(sizeof(T)*sz));

		// 2. ������ ȣ��
		int cnt = 0;
		try
		{
			for (int i = 0; i < size; i++)
			{
				//new(&buff[i]) T;		// ����Ʈ ������ ȣ��..
				new(&buff[i]) T(value); // ���� ������ ȣ��� �ʱ�ȭ.
				++cnt;
			}
		}
		catch (...)
		{
			// ������ ȣ�⿡ ������ ��� ��ü�� �Ҹ��ڸ� ȣ���ؾ� �Ѵ�.
			for (int i = 0; i < cnt; i++)
				buff[i].~T();

			operator delete(buff);
			buff = nullptr;
		}
	}
	~vector() 
	{
		if (buff)
		{
			for (int i = 0; i < size; i++)
				buff[i].~T();

			operator delete(buff);
		}
	}
};

int main()
{
	//vector<int> v(10);

	vector<Point> v(10, Point(0,0) ); // �ʱ�ȭ�� ����� ��ü�� 2��° ���ڷ� ����

}