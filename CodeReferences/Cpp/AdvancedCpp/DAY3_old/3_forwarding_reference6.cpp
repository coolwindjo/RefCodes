#include <iostream>

// STL �� vector�� ������ ������ ���ô�.

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

// vector<bool> �� Ư��ȭ �Ǿ� �ֽ��ϴ�.
template<> class vector<bool>
{
	int* buff;
	int size;
public:
	vector(int sz) : size(sz) {	buff = new int[(sz / 32) + 1];	}

	// �Ʒ� �ڵ尡 "temporary proxy" ��� �̸��� ���� ��� �Դϴ�.
	class BitProxy
	{
		int* buff;
		int idx;
	public:
		BitProxy& operator=(bool b)
		{
			printf("%p�ּ��� %d �ε�����° ��Ʈ�� %d�� ä���\n", buff, idx, b);
			return *this;
		}
		// BitProxy => bool���� �Ͻ��� ��ȯ ���
		operator bool()
		{
			printf("%p�ּ��� %d �ε�����° ��Ʈ�� ��ȯ\n", buff, idx);
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

	v[2] = 1; // BitProxy�ӽð�ü = 0 
			  // BitProxy�ӽð�ü.operator=( bool) �Լ��� ������ �˴ϴ�.

	bool b1 = v[0]; // bool b1 = BitProxy�ӽð�ü
					//         = BitProxy�ӽð�ü.operator bool() 
	
}




/*

int main()
{
	// �� ������ 
	vector<int> v1(10);  // �� ���� �翬�ϴ�..
	v1[0] = 10;

	vector<bool> v2(10);

}
*/
// �����ҽ��� ī�信 �ֽ��ϴ�
