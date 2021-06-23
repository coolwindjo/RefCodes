#include <iostream>

// STL 의 vector의 구현을 생각해 봅시다.

template<typename T> class vector
{
	T* buff;
	int size;
public:
	vector(int sz) : size(sz)
	{
		buff = new T[size]; 
	}
	T& operator[](int idx) { return buff[idx]; }
};

// vector<bool> 은 특수화 되어 있습니다.
template<> class vector<bool>
{
	int* buff;
	int size;
public:
	vector(int sz) : size(sz) {	buff = new int[(sz / 32) + 1];	}

	// 아래 코드가 "temporary proxy" 라는 이름을 가진 기술 입니다.
	class BitProxy
	{
		int* buff;
		int idx;
	public:
		BitProxy& operator=(bool b)
		{
			printf("%p주소의 %d 인덱스번째 비트를 %d로 채운다\n", buff, idx, b);
			return *this;
		}
		// BitProxy => bool로의 암시적 변환 허용
		operator bool()
		{
			printf("%p주소의 %d 인덱스번째 비트를 반환\n", buff, idx);
			return 0;
		}
		BitProxy(int* p, int n) : buff(p), idx(n) {}
	};
	BitProxy operator[](int idx) { return BitProxy(buff, idx); }
};
int main()
{
//	vector<bool> v = { 1,1,1,1,1 };
	vector<bool> v(10);

	v[2] = 1; // BitProxy임시객체 = 0 
			  // BitProxy임시객체.operator=( bool) 함수가 있으면 됩니다.

	bool b1 = v[0]; // bool b1 = BitProxy임시객체
					//         = BitProxy임시객체.operator bool() 
	
}




/*

int main()
{
	// 위 구현은 
	vector<int> v1(10);  // 이 경우는 당연하다..
	v1[0] = 10;

	vector<bool> v2(10);

}
*/
// 오전소스는 카페에 있습니다
