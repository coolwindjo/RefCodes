#include "../../ProbSolvStart.h"

typedef list<int> li;

int N;//직원 수
int S;//시작 직원 번호
int M;

void InputData(){
	cin >> N >> S >> M;
}
int main(){

	InputData();//	입력 함수

	//	코드를 작성하세요
	int curN = N;
	int curS = S-1;
	const int constM = M-1;
	
	li numL;
	FOR(i, curN){
		numL.push_back(i+1);
	}
	
	li::iterator it = numL.begin();
	
	FOR(i, N){
		int chosen = (curS+constM)%curN;
		
		advance(it, chosen);
		cout << *it << " ";
		numL.erase(it);
		it = numL.begin();
		
		curS = chosen;
		curN = numL.size();
	}
	
	return 0;
}