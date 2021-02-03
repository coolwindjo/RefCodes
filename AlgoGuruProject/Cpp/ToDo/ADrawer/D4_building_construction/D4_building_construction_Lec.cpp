#include <iostream>
using namespace std;
#define MAXN (10)
#define INF (100 * 10 + 10)
int N;//빌딩개수(장소개수)
int cost[MAXN+1][MAXN+1];//[빌딩][장소]=비용
int sol;//최소비용
int used[MAXN+1];//장소사용 유무
void InputData(){
    cin >> N;
    for (int i=1; i<=N; i++){//빌딩 인덱스
        for (int j=1; j<=N; j++){//장소 인덱스
            cin >> cost[i][j];
        }
    }
}
void DFS(int n, int sum){//건물인덱스, 누적비용
    if (sol <= sum) return;//가지치기, 중간 누적비용이 이전 답보다 좋지 않으므로...
    if (n > N){//종료조건
        sol = sum;
        return;
    }
    for (int i=1; i<=N; i++){//장소 인덱스
        if (used[i] == 1) continue;//i장소 이미 사용중.
        used[i]=1;//표시
        DFS(n+1, sum + cost[n][i]);
        used[i]=0;//표시 제거
    }
}
int Solve(){
    sol = INF;//최솟값 구하므로 최댓값으로 초기화
    DFS(1, 0);//건물인덱스, 누적비용
    return sol;
}
int main(){
    InputData();
    int ans = Solve();
    cout << ans << endl;
    return 0;
}
 
/**************************************************************
    Problem: 2865
    User: SWT01005
    Language: C++
    Result: Accepted
    Time:3 ms
    Memory:2084 kb
****************************************************************/