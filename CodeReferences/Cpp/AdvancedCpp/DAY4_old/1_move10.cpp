#include <vector>
#include "cppmaster.h"
using namespace std;

class Data
{
public:
	Data() = default;
	Data(const Data& d) { LOG_FUNCTION_NAME(); }
	Data& operator=(const Data&) { LOG_FUNCTION_NAME(); return *this; }

	Data(Data&& d) { LOG_FUNCTION_NAME(); }
	Data& operator=(Data&&) { LOG_FUNCTION_NAME(); return *this; }
};
// �ٽ� : "Const Object �� move �ɼ� ����." 
//			std::move() ���� "��������� ȣ��"
int main()
{
	Data d1;
	Data d2 = d1;			 // ���� ������ ȣ��
	Data d3 = std::move(d1); // move ������

	const Data d4; // ��� ��ü
	Data d5 = d4;			
	Data d6 = std::move(d4); // ���� ������ ȣ��. �����ü�� move�ɼ� ����.
				// static_cast< d4Ÿ�� &&>(d4);
				// static_cast< const Data &&>(d4);  �̹Ƿ�
				//				=> Data(Data&& d) �� ���� ����.
				//				=> Data(const Data& d) �� ���� �ִ�.
}