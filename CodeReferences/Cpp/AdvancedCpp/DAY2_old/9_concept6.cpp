#include <iostream>
#include <iterator>
#include <vector>
#include <list>

// advance 만들기
template<typename T> requires std::input_iterator<T>
void advance(T& p, int N)
{
	std::cout << "++로 이동" << std::endl;
	while (N--) ++p;
}

template<typename T> requires std::random_access_iterator<T>
void advance(T& p, int N)
{
	std::cout << "+로 이동" << std::endl;
	p = p + N;
}

template<typename T> requires std::random_access_iterator<T>
void sort(T first, T last)
{
	std::cout << "random" << std::endl;
}

template<typename T> requires std::bidirectional_iterator<T>
void sort(T first, T last)
{
	std::cout << "bidirectional_iterator" << std::endl;
}

int main()
{
//	std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10 }; // 임의접근 반복자, ++ 과 + 모두 가능.
	std::list<int>   v = { 1,2,3,4,5,6,7,8,9,10 }; // 양방향 반복자, ++, -- 만 가능
	//												// 입력 반복자,  ++ 만 가능
	auto p = v.begin();

	// p를 5칸 전진하고 싶다..
	// p = p + 5 ; // vector 일때는 ok.. list 라면 에러
	//++p; ++p; ++p; ++p; ++p; // 모두 ok.. 하지만 vector라면 느리다.!
	advance(p, 5); // ok.. 최선의 코드

	sort(v.begin(), v.end()); // vector라면 ok.. list 는 error
								// v.sort() list의 경우.
}