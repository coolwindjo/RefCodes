#include "../../ProbSolvStart.h"

const int MAX_N = 150000 + 10;
int N;//버섯 수
int P[MAX_N];//버섯 값

void InputData(){
	cin >> N;
	for (int i = 0; i < N; i++){
		cin >> P[i];
	}
}

int main(){

	InputData();			//	입력 함수

	//	코드를 작성하세요
	int ud = 1;	
	int ans = 0;
	for (int i=0; i<N; i++){
		const int val = P[i];
		const int next = P[i+1];
		if(ud == 1){
			if(val > next){
				// go down
				ans += val;
				ud = -1;
			}
		}
		else{
			if(val < next){
				// go up
				ans -= val;
				ud = 1;
			}
		}	
	}
	
	cout << ans << endl;	//	정답 출력
	return 0;
}

