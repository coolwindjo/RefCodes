#include <iostream>
#include <thread>
#include <atomic>  // C++11 

//int obj = 0; // 전역 변수.. 스레드에 안전하지 않다.

std::atomic<int> obj = 0; // 멀티 스레드에 안전한 int

int main()
{
	++obj;				// ok. 멀티스레드에 안전합니다.
	
	obj.fetch_add(1);	// ok. 멀티스레드에 안전합니다.
			// 1. OS 가 가진 mutex 등으로 동기화 할것이다.
			// 2. CPU 이 명령으로 동기화 할것이다. - CPU 가 가진 lock 등의 명령사용

	std::cout << obj.is_lock_free() << std::endl; 

	int n = obj;
}
