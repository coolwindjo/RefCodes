// 4_FUNCTOR1
#include <iostream>
#include <bits/stdc++.h>

// �Լ� ��ü (Function Object, Functor)
// () �����ڸ� ������ �ؼ� �Լ�ó�� ��밡���� ��ü

// "���¿� ����"�� ������ �Լ�!
// "�Լ� ��ü"��� ��� ��� "callable object"

// callable object: ()�� ȣ�� ������ ��� �� => �Լ�, �Լ���ü, Lambda expression
class URandom
{
	int idx;
	int history[10];
public:
	URandom(){idx = 0; memset(history, -1, sizeof(history)); }
	void reset_history() {}
	int operator()()
	{
		// Member data�� ���ؼ� ���¸� ����
		while (idx < 10) {
			const int num = rand() % 10;
			int i = 0;
			while (history[i++] != num) {
				if (i == 10){
					history[idx++] = num;
					// std::cout<< "history[" << idx-1 << "] : " << num <<std::endl;
					return num;
				}
			}
		}
		return -1;
	}

};


int main()
{
	URandom urand;
	// urand();	// �Լ� ó�� ����� �� �ְ� �Ϸ���,
				// urand.operator()() �� �Ǹ� �˴ϴ�.
				// urand.next() ??
	for (int i = 0; i < 10; i++)
		std::cout << urand() << std::endl;
}