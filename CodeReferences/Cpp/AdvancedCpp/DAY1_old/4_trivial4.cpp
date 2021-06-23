#include <iostream>
#include <thread>
#include <atomic>  // C++11 

//int obj = 0; // ���� ����.. �����忡 �������� �ʴ�.

std::atomic<int> obj = 0; // ��Ƽ �����忡 ������ int

int main()
{
	++obj;				// ok. ��Ƽ�����忡 �����մϴ�.
	
	obj.fetch_add(1);	// ok. ��Ƽ�����忡 �����մϴ�.
			// 1. OS �� ���� mutex ������ ����ȭ �Ұ��̴�.
			// 2. CPU �� ������� ����ȭ �Ұ��̴�. - CPU �� ���� lock ���� ��ɻ��

	std::cout << obj.is_lock_free() << std::endl; 

	int n = obj;
}
