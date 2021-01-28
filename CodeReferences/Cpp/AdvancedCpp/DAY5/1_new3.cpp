#include "cppmaster.h"
#include <vector>

class DBConnect {};

int main()
{
	// DBConnect 가 생성자에서 DB에 접속한다고 생각해 보세요
	std::vector<DBConnect> v(5);

	v.resize(3); // 이순간의 코드 구현을 생각해 봅시다.
				// 줄어든 2개의 객체에 대해
				// 메모리는 파괴하지 않지만
				// "소멸자는 명시적으로 호출해서 DB disconnect"

	v.resize(4); // 추가된 객체를 위한 메모리는 이미 있습니다.
				// 하지만, 생성자를 다시 호출해서
				// DB에 접속해야 합니다.
				// "생성자의 명시적 호출이 필요 합니다."


}






/*
int main()
{
	std::vector<int> v(10);

	v.resize(7);

	std::cout << v.size() << std::endl; // 7
	std::cout << v.capacity() << std::endl; // 10

	v.push_back(0); // 끝에 한개 추가

	std::cout << v.size() << std::endl;     // 8
	std::cout << v.capacity() << std::endl; // 10

	v.shrink_to_fit(); // 필요없는 여분의 메모리 제거

	std::cout << v.size()     << std::endl; // 8
	std::cout << v.capacity() << std::endl; // 8

	v.push_back(0); // 끝에 한개 추가

	std::cout << v.size() << std::endl;     // 9
	std::cout << v.capacity() << std::endl; // 12
}
*/