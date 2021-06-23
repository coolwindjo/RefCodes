// 3_forward8
#include <vector>
#include <type_traits>
template<typename T> class List
{
public:
	List(int sz, T value) {}

	template<typename C>
	//List(C c) {}	// call by value : ���纻�� �������
	//List(C& c) {}	// call by reference : �ӽð�ü ������ ����.
	//List(const C& c) {} // const lvalue reference : move �� �ȵ�.
	List(C&& c) {}
};
template<typename C>
//List(C&& c)->List< typename C::value_type >; // vector<int>&::value_type �ϴ� �ڵ� �� ����.
List(C&& c)->List< typename std::remove_reference_t<C>::value_type >;


int main()
{
	List  s1(10, 3);  
	
	std::vector<int> v = { 1,2,3 };


	List s2(v); // v �� lvalue �̹Ƿ�
				// C�� Ÿ���� : "vector<int>" �� �ƴϰ�, "vector<int>&" �Դϴ�.


//	f4(n); // T : int& 


	List s3(std::vector<int>{1, 2, 3}); // �ӽð�ü
}

/*
struct A
{
	typedef int value_type;
};
A::value_type n; // ok
A&::value_type n; // error
*/

// ������ �ɼ� : /std:c++latest �߰��ϼ���..