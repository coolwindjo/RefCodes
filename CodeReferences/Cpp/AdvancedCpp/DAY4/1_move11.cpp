#include <iostream>
#include <string>
#include <vector>
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
	// call by value - ���纻�������� ���� �ʴ�.
	// void setData(Data d) { data = d; }

	// 1. const & ��� - C++98���� ���� �߿��ߴ� ���
	//void setData(const Data& d) { data = d; }				// ������ ����
	//void setData(const Data& d) { data = std::move(d);	}	// ������ ���� - const �̹Ƿ�

	// ��� 1. 2���� setter
	//void setData(const Data& d) { data = d; }
	//void setData(Data&& d)      { data = std::move(d); }

	// ��� 2. call by value �� ���� ������尡 Ŭ�� ?
	// move �迭 �Լ��� ����� ���� Ÿ���̸�, call by value �� ������ �ʴ�.
	// ���1 ���� ������ ������ "�Ѱ��� �Լ�"�� move�� �����Ҽ� �ֵ� �ȴ�.
	// void setData(Data d) { data = std::move(d); }


	// ��� 3. "���1"�� 2���� �Լ��� �ڵ������Ҽ� ������ ? - "forwarding reference"
	
	// lvalue(d)			 => setData(U& d)
	// rvalue(std::move(d))  => setData(U&& d)
	template<typename U> void setData(U&& d)
	{
		// ������ �´°��� ?
		//data = d;			// ������ ����
		//data = std::move(d);// ������ �̵�

		// ���⼭ �ʿ��Ѱ�.. ���ڷ� lvalue�� ���� ���簡 ȣ��ǵ��� lvalue ĳ����...
		// ���ڷ� rvalue�� ���� move�� ȣ��ǵ��� rvalue ĳ����...
		// data = static_cast<U&&>(d);
		data = std::forward<U>(d);
	}
};

int main()
{
	Data d;

	Test test;

	test.setData(d); // ������� 1ȸ ȣ��.
					 // ������� 1ȸ, move ���� 1ȸ

	test.setData(std::move(d)); // move ���� 1ȸ
								// move ���� 1ȸ, move���� 1ȸ
				// static_cast<Data&&>(d);
}








