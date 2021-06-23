


// ī��(cafe.naver.com/cppmaster) ���� 4���� ���� �ҽ� �����ø� �˴ϴ�.





#include <iostream>
#include <string>
#include <vector>

int main()
{
	std::string s1 = "hello";
	//std::string s2 = s1;	        // s1�� �ڿ��� ����
	std::string s2 = std::move(s1); // s1�� �ڿ��� �̵�
	
	std::cout << s1 << std::endl; // ""
	std::cout << s2 << std::endl; // "hello"


	std::vector<int> v1(10, 3); 
	//std::vector<int> v2 = v1; // v1�� �ڿ��� ����
	std::vector<int> v2 = std::move(v1);// v1�� �ڿ��� v2�� �̵�

	std::cout << v1.size() << std::endl; // 0
	std::cout << v2.size() << std::endl; // 10
}

