#include <thread>
#include <functional>

void foo(int a, int& b) { b = 100; }

int main()
{
	
	int n = 0;

	// C++11 ������ ����
//	std::thread t(&foo, 10, n);  // n�� ������ ���޵ɱ�� ? ������ �ɱ�� ?
								// �⺻ ������ "�� ���"���� ����..

	std::thread t(&foo, 10, std::ref(n));

	t.join();
}