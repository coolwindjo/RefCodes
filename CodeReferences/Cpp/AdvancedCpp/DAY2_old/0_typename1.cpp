// cafe.naver.com/cppmaster ���� 
// 2���� �����ҽ��� �����ø� �˴ϴ�.

// �ٽ� : ���ø��� �����ؼ� Ÿ���� �������� �ݵ�� typename �� ����� �Ѵ�.
//  typename T::DWORD * p;

class Test
{
public:
	enum { value = 1 };
	typedef int DWORD;
};
int p = 0;

template<typename T> void foo(T a)
{
	// �Ʒ� 2�ٿ��� * �� �ǹ̸� ������ ������(1. ���ϱ�, 2. ������ ���� ����)
	// Ŭ�����̸�::"�̸�"   => �� �Ǵ� Ÿ��
	//Test::value * p; // ���ϱ��� �ǹ�.
	//Test::DWORD * p; // ������ ���� ����

	// �Ʒ� �ڵ� �ؼ��� ������
	// T::�̸�          => ������ �ؼ�.
	// typename T::�̸� => ���� �ƴ� �̸����� �ؼ��� �޶�.
	T::value * p; // ok..
//	T::DWORD * p; // error.
	typename T::DWORD * p; // ok.

	
}

int main()
{
	Test t;
	foo(t);
}

