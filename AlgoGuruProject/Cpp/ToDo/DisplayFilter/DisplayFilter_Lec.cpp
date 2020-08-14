#include <iostream>
#define INF ((long long)1<<60)
using namespace std;
int N;	// 필터의 수
int R[11]; // 반사의 정도
int P[11]; // 투과의 정도
long long mindiff;//반사정도 곱과 투과정도 합의 최소 차이
int mincnt;//남길 최소 필터 개수
long long ABS(long long x){ return (x < 0) ? -x : x; }
void DFSmulti(int s,  int cnt,  long long mul,  long long sum){//시작인덱스,  선택개수,  반사정도곱,  투과정도합
    if (cnt != 0){
        long long diff = ABS(mul - sum);
        if ((mindiff > diff) ||
            ((mindiff == diff) && (mincnt > cnt))){
            mindiff = diff;
            mincnt = cnt;
        }
    }
    for (int i=s; i<=N; i++){
        DFSmulti(i+1,  cnt+1,  mul * R[i],  sum + P[i]);
    }
}
void DFSbt(int n,  int cnt,  long long mul,  long long sum){
    if (cnt != 0){
        long long diff = ABS(mul - sum);
        if ((mindiff > diff) ||
            ((mindiff == diff) && (mincnt > cnt))){
            mindiff = diff;
            mincnt = cnt;
        }
    }
    if (n > N) return;//종료 조건
    DFSbt(n+1,  cnt+1,  mul * R[n],  sum + P[n]);//n번 필터 선택하는 경우
    DFSbt(n+1,  cnt,  mul,  sum);////n번 필터 선택 안하는 경우
}
int Solve(){
    mindiff = INF;
    //DFSmulti(1,  0,  1,  0);//시작인덱스,  선택개수,  반사정도곱,  투과정도합
    DFSbt(1,  0,  1,  0);//필터 인덱스,  선택개수,  반사정도곱,  투과정도합
    return N - mincnt;//총개수 - 남길개수 = 제거개수
}
void InputData(void){
	cin >> N;
	for(int i=1; i<=N; i++)  cin >> R[i] >> P[i];
}
int main(){
	int ans = -1;
	InputData(); // 입력함수

	ans = Solve();// 코드를 작성 하세요

	cout << ans << endl;//출력
	return 0;
}