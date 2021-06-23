// 6_enable_if1.cpp

// C++11 ǥ�ؿ� �ִ� �ڵ��Դϴ�
template<bool, typename T = void > struct enable_if
{
	typedef  T type;
};

template<typename T> struct enable_if<false, T> 
{
};

int main()
{
	// �Ʒ� �ڵ忡�� �� ������ Ÿ���� ?
	enable_if<true, int>::type  n1; // int n1
	enable_if<true>::type       n2; // void n2  �̹Ƿ� error,
	enable_if<false, int>::type n3; // ::type �� �����Ƿ� ������ ����.

	// �ٽ�
	// enable_if<true, Ÿ��>::type   �� "Ÿ��"
	// enable_if<false, Ÿ��>::type  �� ::type�� ���ٴ� ����.
}