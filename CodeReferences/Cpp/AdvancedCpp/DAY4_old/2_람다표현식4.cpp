#include <algorithm>
#include <functional>  
#include <vector>
#include <iostream>
using namespace std;

class ClosureType
{
//	int v1, v2;
public:
	ClosureType() = delete;
	inline auto operator()(int a, int b) const
	{
		return a + b;
	}
};
int main()
{
	auto f1 = [](int a, int b) { return a + b; };

	std::cout << typeid(f1).name() << std::endl;

	// �Ʒ� �ڵ���� ������ ������
	decltype(f1) f2;		// error. �����Ϸ��� ���� Ÿ�Կ��� ����Ʈ �����ڰ� "delete" 
							// �Ǿ� �ֽ��ϴ�.
	decltype(f1) f3 = f1;  // ok.. ���� �����ڴ� ok..

		// C++20 ���ʹ� ĸ������ ���� ǥ������ ����Ʈ ������ ����.
		// ��, ĸ���� ���ٴ� ��� ����Ʈ ������ �ȵ˴ϴ�.
}






