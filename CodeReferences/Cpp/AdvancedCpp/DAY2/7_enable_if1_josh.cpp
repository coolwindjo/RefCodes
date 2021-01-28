// 6_enable_if1.cpp

// C++11 ǥ�ؿ� "�״��" �ִ� Code�Դϴ�.
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
	enable_if<true>::type       n2; // void n2 -> Error
	enable_if<false, int>::type n3; // type �� �����Ƿ� Compile error 

	// �ٽ�
	// enable_if<true, TYPE>::type �� "TYPE"
	// enable_if<false, TYPE>::type �� ::type�� ���ٴ� Error
}