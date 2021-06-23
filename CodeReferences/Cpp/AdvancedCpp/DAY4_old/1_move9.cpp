#include <vector>
#include "cppmaster.h"
using namespace std;

class Data
{
public:
	Data() = default;
	Data(const Data& d)     { LOG_FUNCTION_NAME(); }
	Data& operator=(const Data&) { LOG_FUNCTION_NAME(); return *this; }

	// move �迭 �Լ��� ���鶧
	// 1. �ǵ��� ���ܰ� ���� �ڵ常 ����ϼ���
	// 2. �׸���, ���ܰ� ������ �����Ϸ����� �˷��ּ��� - �ٽ�

	Data(Data&& d) noexcept          { LOG_FUNCTION_NAME(); }
	Data& operator=(Data&&) noexcept { LOG_FUNCTION_NAME(); return *this; }
};

int main()
{
	Data d1;
	Data d2 = d1; // ������ ����
	Data d3 = std::move(d1); // ������ move
	Data d4 = std::move_if_noexcept(d2); // move �����ڿ� ���ܰ� �������� move ������ ���
										 // ���ܰ� ������ ���� ������ ���

	std::vector<Data> v(5);

	cout << "-----" << endl;

	v.resize(10); // �̼��� std::move_if_noexcept �� ����ؼ� �̵��մϴ�.
	
	cout << "-----" << endl;
}