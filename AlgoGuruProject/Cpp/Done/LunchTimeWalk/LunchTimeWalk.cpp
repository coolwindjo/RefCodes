#include "../../ProbSolvStart.h"

int N;//직원 수
int T;//산책 시간(분단위)
int P[100000 + 10];//직원 출발 위치
int S[100000 + 10];//직원 산책 속도(분당)

void InputData(){
	cin >> N >> T;
	for (int i = 0; i < N; i++){
		cin >> P[i] >> S[i];
	}
}

const int MAX_NUM = 100000 + 10;
int ComputeNumGroups(const int numWalkers, const int timeStep, const int (&speed)[MAX_NUM],
					 const int (&position)[MAX_NUM]){
	int numGroups = 0;

	long long nextPosLastWkr = position[numWalkers-1] + (long long)speed[numWalkers-1]*timeStep;
	if (numWalkers > 1){
		++numGroups;
		for (int i=(numWalkers-2); i>=0; --i){
			long long nextPos = position[i] + (long long)speed[i]*timeStep;
			if (nextPos >= nextPosLastWkr){
				nextPos = nextPosLastWkr;
			}
			else{
				++numGroups;
			}
			nextPosLastWkr = nextPos;
		}
	}
	return numGroups;
}

int main(){
	int ans = -1;

	InputData();			//	입력 함수

	//	코드를 작성하세요
	ans = ComputeNumGroups(N, T, S, P);
	
	cout << ans << endl;	//	정답 출력
	return 0;
}