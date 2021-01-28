// 4_FUNCTOR1
#include <iostream>
#include <bits/stdc++.h>

// 함수 객체 (Function Object, Functor)
// () 연산자를 재정의 해서 함수처럼 사용가능한 객체

// "상태와 동작"을 가지는 함수!
// "함수 객체"라는 용어 대신 "callable object"

// callable object: ()로 호출 가능한 모든 것 => 함수, 함수객체, Lambda expression
class URandom
{
	int idx;
	int history[10];
public:
	URandom(){idx = 0; memset(history, -1, sizeof(history)); }
	void reset_history() {}
	int operator()()
	{
		// Member data를 통해서 상태를 관리
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
	// urand();	// 함수 처럼 사용할 수 있게 하려면,
				// urand.operator()() 가 되면 됩니다.
				// urand.next() ??
	for (int i = 0; i < 10; i++)
		std::cout << urand() << std::endl;
}