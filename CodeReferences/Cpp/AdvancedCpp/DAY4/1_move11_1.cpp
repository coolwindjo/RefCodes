#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include "cppmaster.h"

class Data
{
public:
	Data() = default;
	Data(const Data& d) { LOG_FUNCTION_NAME(); }
	Data& operator=(const Data&) { LOG_FUNCTION_NAME(); return *this; }
	Data(Data&& d) { LOG_FUNCTION_NAME(); }
	Data& operator=(Data&&) { LOG_FUNCTION_NAME(); return *this; }
};
// �ٽ� : move�� �����ϴ� setter �����.
class Test
{
	Data data;
public:
	// ���.. ���� �ڵ忡���� setter �� 2���� setter�� �����ϴ°��� ���� �������� 
	// �����ϴ�.

	// ���ø��� "�ٸ� ��� �ʿ��Ҷ��� �ֽ��ϴ�."

	// 2���� setter vs "U&&" �� ������.
//	void setData(const Data& d) { data = d; }
//	void setData(Data&& d)      { data = std::move(d); }

	// �� ����� forwarding reference �� ���� 
	//    : Data Ÿ�Կ� ���ؼ��� 2���� �����Ǵ� ���� �ƴ϶�,, 
	//		��� Ÿ�Կ� ���ؼ� setData�� �����ǰ� �ִ�.
	// is_same_v<Data&, Data> => ���� Ÿ������ �ϰ�ʹ�.
	// is_same_v<const Data, Data> => ���� Ÿ������ �ϰ�ʹ�.
	// std::decay_t<U> => const�� reference�� ������ Ÿ�� ���ϱ�
	// std::remove_cref_t<U> => C++20���ʹ� �̷��� ���. 

	template<typename U> 
	std::enable_if_t< std::is_same_v< std::decay_t<U>, Data> > 
	setData(U&& d)
	{
		data = std::forward<U>(d);
	}

	void setData(double d) { std::cout << "double" << std::endl; }
};

int main()
{
	Data d;
	Test test;
	test.setData(d); // �̼��� U�� Ÿ���� ?
					// 1. Data   2. Data& => ���� 2
					// is_same_v<Data&, Data>   ===> false �̹Ƿ� setData�� ���ø�����
					//									���ȵ�.

					// f4(n)  => T : int&

	test.setData(std::move(d)); 
	test.setData(3.4f);
}





// ���� �ҽ��� ī�信 �÷� ���ҽ��ϴ�.


