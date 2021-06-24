#include <iostream>
#include <thread>
#include <atomic>	// C++11

/*/
int obj = 0;	// Global variable ... thread safe X
/*/
std::atomic<int> obj = 0;	// Thread safe int
//*/

int main()
{
	++obj;				// Thread safe
	obj.fetch_add(1);	// Thread safe
	// 1. OS가 가진 mutex 등으로 동기화 할 것?
	// 2. CPU 가 명령으로 동기화 할 것? => Answer!
	std::cout << std::boolalpha << obj.is_lock_free() <<std::endl;

	int n = obj;
	std::cout << n <<std::endl;

}
