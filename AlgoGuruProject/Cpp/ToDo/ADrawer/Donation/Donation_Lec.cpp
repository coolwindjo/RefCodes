#include <iostream>
using namespace std;

int N;//직원 수
int M;//기부금 총액
int A[1000010];//직원 별 성과급
void InputData(){
	cin >> N >> M;
	for (int i = 0; i < N; i++){
		cin >> A[i];
	}
}
bool isPossible(int m){//m상한액,  상한액 초과면 초과분이 기부금,  이하면 기부금은 0원
    int sum = M;
    for (int i=0; i<N; i++){
        if (A[i] <= m) continue;
        sum -= A[i] - m;
        if (sum <= 0) return true;//가능
    }
    return false;//불가능
}
int Solve(){
    int s=0,  e=0,  sol=0;
    //1.직원 성과급 중 max값 구하기(0(s)~max(e) 사이에 존재)
    for (int i=0; i<N; i++){
        if(e < A[i]) e = A[i];
    }
    //2.upper bound 구하기(상한액이 작을수록 기부금이 커짐)
    while(s <= e){
        int m = (s+e)/2;//상한액
        if (isPossible(m)){
            sol=m; s=m+1;
        }
        else{
            e=m-1;
        }
    }
    return sol;
}
int main(){
	int ans = 0;
	InputData();			//	입력 함수
	ans = Solve();//	코드를 작성하세요
	cout << ans << endl;	//	정답 출력
	return 0;
}