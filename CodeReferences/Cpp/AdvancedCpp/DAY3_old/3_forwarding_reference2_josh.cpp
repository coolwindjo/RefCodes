// forwarding reference�� ������ �ǹ�!!

// ��� 1. call by value
//		=> ���纻 ����. user type�̸� overhead�� �ִ�.
// void foo(int n) {}

// ��� 2. call by reference
// 		=> lvalue�� ���� �� �ִ�.
// void foo(int& n) {}

// ��� 3. const lvalue reference
// 		=> ���纻�� ����, lvalue, rvalue ��� ���� �� �ִ�.
//		=> ��, ������� �߰��ȴ�. �б⸸ �����ϰ�, ��� Member�Լ��� ȣ�Ⱑ��	
//								"move �� �� ����"
// void foo(const int& n) {}

// ��� 4. ��������� ��� ��������,
//			2���� �Լ��� ������ ������
// void foo(int&) {}
// void foo(int&&) {}

// ��� 5. "��� 4"�� 2�� �Լ� ������ �����ϴٸ�,
//			2�� �Լ��� �ڵ� �����ǰ� ����.
// 			"forwarding reference"�� ���ڷ� ������ �Լ�!!
template<typename T> void foo(T&& arg) {}

int main()
{
	int n = 10;

	// lvalue �� rvalue�� ��� ������ �ִ� foo �Լ��� ����� �ʹ�
	foo(n);
	foo(10);
}
