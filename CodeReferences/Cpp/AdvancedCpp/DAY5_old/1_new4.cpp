#include "cppmaster.h"

class Point
{
	int x;
	int y;
public:
	// Point 는 디폴트 생성자가 없습니다.
	Point(int a, int b) : x(a), y(b) {}
	~Point() {}
};

// "Generic Container Idioms"
// 컨테이너 설계시 "타입이 가져야 하는 제약조건을"
// 디폴트 생성자로 하지말고 "복사 생성자"로 요구하는 것이 좋다.


template<typename T> class vector
{
	T* buff;
	int size;
	int capacity;
public:
	vector(int sz, const T& value = T() ) : size(sz), capacity(sz)
	{
		// 아래 처럼 코딩하면 T 타입은 반드시 "디폴트생성자가 있어야 한다" 라는 제약이 있게됩니다
		//buff = new T[sz];

		// 1. 메모리 할당
		buff = static_cast<T*> (operator new(sizeof(T)*sz));

		// 2. 생성자 호출
		int cnt = 0;
		try
		{
			for (int i = 0; i < size; i++)
			{
				//new(&buff[i]) T;		// 디폴트 생성자 호출..
				new(&buff[i]) T(value); // 복사 생성자 호출로 초기화.
				++cnt;
			}
		}
		catch (...)
		{
			// 생성자 호출에 성공한 모든 객체는 소멸자를 호출해야 한다.
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

	vector<Point> v(10, Point(0,0) ); // 초기화에 사용할 객체를 2번째 인자로 전달

}