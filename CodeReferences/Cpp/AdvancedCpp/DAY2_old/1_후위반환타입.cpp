// 1_������ȯŸ��

/*
int square(int a)
{
	return a * a;
}
*/
// ���� ��ȯ Ÿ��(suffix return type, trailing return type) �̶�� ����
// C++11 ���� ���Ե� ����
auto square(int a) -> int
{
	return a * a;
}


int main()
{
	square(3);
}