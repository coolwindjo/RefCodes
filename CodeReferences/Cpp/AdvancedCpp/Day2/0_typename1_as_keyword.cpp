class Test
{
public:
	enum { value = 1 };
	typedef int DWORD;
};
int p = 0;

// �ٽ� 1. Template �� �����ؼ� Type�� ���������� �ݵ�� typename�� ����� �Ѵ�.
// typename T::DWORD * p;
template<typename T>
void foo(T a)
{
	// �Ʒ� 2�ٿ��� * �� �ǹ̸� ������ ������(1. ���ϱ�, 2. ������ ���� ����)
	// ClassName::"Name"	=> "Name" can be a value or a type
	/*/
	Test::value * p;	// 1. 
	Test::DWORD * p;	// 2.
	/*/
	// �Ʒ� Code �� �ؼ��غ���
	// T::"Name" 			=> "Name" is a value
	// typename T::"Name"	=> "Name" is a type
	T::value * p;	// OK
#if 0
	T::DWORD * p;	// error 
#else
	typename T::DWORD * p;	// OK
#endif
	//*/
}
int main()
{
	Test t;
	foo(t);
}