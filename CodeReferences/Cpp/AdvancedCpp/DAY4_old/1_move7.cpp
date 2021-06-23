#include <iostream>
#include "cppmaster.h"

class Data
{
public:
	Data() = default;
	Data(const Data& d)			{ LOG_FUNCTION_NAME(); }
	Data& operator=(const Data&) { LOG_FUNCTION_NAME(); return *this; }
	Data(Data&& d)			{ LOG_FUNCTION_NAME(); }
	Data& operator=(Data&&) { LOG_FUNCTION_NAME(); return *this; }
};
//------------------------------------
// ��Ģ 1. ����ڰ� "����" �� "move" �迭 �Լ��� ��� �������� ������
//      ==> �����Ϸ��� ��� ������ �ش�.
//		==> �ڵ������� ���翡���� ��� ����� ����� �ű��
//                     move �Լ������� ��� ����� move�� �ű��

// ��Ģ 2. ����ڰ� "����" �迭 �Լ��� �����ϸ�
//		=> �����Ϸ��� move �� �������� ���Ѵ�. 
//         std::move() ���� "����ڰ� ���� ���� ������"�� ȣ��
//      Ȥ��, ����Ʈ ������ move�� �ʿ� �ϸ� "=default" �������� �����Ϸ����� ��û

// ��Ģ 3. ����ڰ� "move"������ ������ ���
//			===> ���� �迭 �Լ��� ���� �˴ϴ�.
//				 Object(const Object& ) = delete;
//				���� �����ڸ� ����Ҽ� ���ٴ� �ǹ�!!

class Object
{
	Data data;
	std::string name;
public:		  
	Object() {}

	/*
	Object(const Object& obj) : data(obj.data), name(obj.name) {}

	// ���� �� �Լ��� ����Ʈ ������ �ʿ� �ϸ� ��û�Ҽ� �ֽ��ϴ�.
	Object(Object&&) = default;
	Object& operator=(Object&&) = default;
	Object& operator=(const Object&) = default;
	*/
	Object(Object&& obj) : data(std::move(obj.data)), name(std::move(obj.name)) {}
};

int main()
{
	Object o1;

	Object o2 = o1;
	o2 = o1;

	Object o3 = std::move(o1);
	o3 = std::move(o2);
}