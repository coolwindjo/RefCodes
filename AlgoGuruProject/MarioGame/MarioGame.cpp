#include <iostream>
using namespace std;
const int WarnIfNot(const int condFlag, const char* condition)
{
	if(condFlag == 0)
	{
		cout << "Warning: [" << condition << "] is violated!\n";
	}
	return condFlag;
}
#define WARN_IFNOT(cond) WarnIfNot((cond), (#cond))

const int MAX_N = 150000 + 10;
int N;//버섯 수
int P[MAX_N];//버섯 값

void InputData(){
	cin >> N;
	for (int i = 0; i < N; i++){
		cin >> P[i];
	}
}

const int FindMaxH(const int N, const int (&P)[MAX_N])
{
	int h = 0;
	int ud = 1;	
	for (int i=0; i<N; i++){
		if(ud == 1){
			if(P[i] > P[i+1]){
				// go down
				h += P[i];
				ud = -1;
			}
		}
		else{
			if(P[i] < P[i+1]){
				// go up
				h -= P[i];
				ud = 1;
			}
		}	
	}
	
	return h;
}

int main(){
	int ans = -1;

	InputData();			//	입력 함수

	//	코드를 작성하세요
	ans = FindMaxH(N, P);
	
	cout << ans << endl;	//	정답 출력
	return 0;
}

