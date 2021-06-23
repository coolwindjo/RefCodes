


// 카페(cafe.naver.com/cppmaster) 에서 4일차 사전 소스 받으시면 됩니다.





#include <iostream>
#include <string>
#include <vector>

int main()
{
	std::string s1 = "hello";
	//std::string s2 = s1;	        // s1의 자원을 복사
	std::string s2 = std::move(s1); // s1의 자원을 이동
	
	std::cout << s1 << std::endl; // ""
	std::cout << s2 << std::endl; // "hello"


	std::vector<int> v1(10, 3); 
	//std::vector<int> v2 = v1; // v1의 자원을 복사
	std::vector<int> v2 = std::move(v1);// v1의 자원을 v2로 이동

	std::cout << v1.size() << std::endl; // 0
	std::cout << v2.size() << std::endl; // 10
}

