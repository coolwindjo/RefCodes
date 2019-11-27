// �ζ��� �Լ��� �Լ� �������� �̾߱�
// VS2015�� ������ ��� ������Ʈ
// cl 4_FunctionAndStrategy_2.cpp /FAs /Ob1
// Assembly ���� ����� /FAs
// inline : ����ȭ ��� /Ob1
// ����ó����� ���� /EHsc

// gcc������ inline ����ȭ ����� -O2 �̴�.

// 1. inline ġȯ�� Compile �ð� ����
// 2. inline function�̶� funtion pointer�� ��Ƽ� ȣ���ϸ� inline ġȯ �� �� ����.
//      (function pointer�� �ᱹ �����̴�. ����ð��� ����� �� �ִ�.)
int add1(int a, int b)
{
    return a + b;
}
inline int add2(int a, int b)
{
    return a + b;
}

int main()
{
    int n1 = add1(10, 20);  // ȣ��
    int n2 = add2(10, 20);  // ġȯ

    int (*f)(int, int) = &add2;
    f(10, 20);              // ȣ��
}