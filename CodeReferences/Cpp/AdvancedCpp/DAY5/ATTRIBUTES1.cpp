// ATTRIBUTES1
#include <iostream>

// ������ ������ "foo" �� ���ο� ������ ���Դ�.
// [[���]] : attributes, �����Ϸ����� ����

//	g++ : void foo() __attributes__(( ��� ))
//  vc  : __declspec(���) void foo()

[[deprecated("please use foo_v2")]] void foo() {}

void foo_v2() {}

int main()
{
	foo();
}