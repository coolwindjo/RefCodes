#include <thread>
#include <functional>

void foo(int a, int& b) { b = 100; }

int main()
{
	
	int n = 0;

	// C++11 스레드 생성
//	std::thread t(&foo, 10, n);  // n이 값으로 전달될까요 ? 참조로 될까요 ?
								// 기본 동작은 "값 방식"으로 전달..

	std::thread t(&foo, 10, std::ref(n));

	t.join();
}