#include <algorithm>
#include <functional>  
#include <vector>
using namespace std;

// ���� ǥ������ ����
// Lambda expression�� ���� compiler�� ���� class
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
};

int main()
{
	// std::vector<int> v = { 1,2,3,4,5,6,7,8,9,10 };
	// auto p = std::find_if(std::begin(v), std::end(v), [](int a) { return a % 3 == 0; });

	// auto f1 = [](int a, int b) { return a + b; };

	// Lambda expression: compiler�� ������ Class�� �ӽ� ��ü
	auto f1 = ClosureType();

	// �Լ�ó�� ��밡��
	int n = f1(1, 2);	// f1.operator()(1, 2) �� ���

	// ���� �� Error�� ������.
	auto 		a1 = [](int a, int b) { return a + b; };	// OK
	// auto& 		a2 = [](int a, int b) { return a + b; };	// Error
	const auto&	a3 = [](int a, int b) { return a + b; };	// OK
	auto&& 		a4 = [](int a, int b) { return a + b; };	// OK
}






