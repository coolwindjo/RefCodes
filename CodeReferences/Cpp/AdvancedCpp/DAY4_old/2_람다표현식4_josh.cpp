#include <iostream>
#include <algorithm>
#include <functional>  
#include <vector>
using namespace std;

class ClosureType
{
private:
	
public:
	ClosureType() {}
	~ClosureType() {}
	inline auto operator()(int a, int b) const
	{
		return a + b;
	}
	// static inline auto helper()(int a, int b)
	// {
	// 	return a + b; // error. static ��� �Լ��� ��� ����Ÿ ������ �ȵȴ�
	// }
	// typedef int(*F)(int, int);

	// operator F() { return &Closure::helper; } 
};

int main()
{
	auto f1 = [](int a, int b) { return a + b; };

	std::cout<< typeid(f1).name() <<std::endl;

	// �Ʒ� Code���� �����غ�����.
	decltype(f1)	f2;			// error: Compiler�� ���� Type���� default �����ڰ� "delete" ������
	decltype(f1)	f3 = f1;	// OK: ��������ڴ� OK

	// C++20 ���ʹ� Capture ���� ���� Lambda expression�� default ������ ����
	// ��, Capture�� Lambda�� ��� Default ������ �ȵ˴ϴ�.

	return 0;
}






