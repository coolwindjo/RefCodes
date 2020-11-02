#include <stdio.h>
#define MAXN (20)
#define INF (MAXN * MAXN)
int N;//벽장개수
int sl, sr;//초기에 열여있는 벽장 번호
int M;//사용할 벽장 순서 개수
int seq[MAXN+10];//사용할 벽장 번호
int movecnt;//최소 이동 횟수
int ABS(int x) { return (x<0) ? -x : x; }
void DFS(int m, int left, int right, int cnt){
    if (movecnt <= cnt) return;//가지치기, 이미 이전 답보다 않좋음
    if (m >= M){//종료조건, 모든 순서 다 했음
        movecnt = cnt;//답 갱신
        return;
    }
    if (seq[m] < right) DFS(m+1, seq[m], right, cnt + ABS(seq[m] - left));
    if (seq[m] > left) DFS(m+1, left, seq[m], cnt + ABS(right - seq[m]));
}
int Solve(){
    movecnt = INF;//최솟값 구하므로 최댓값으로 초기화
    DFS(0, sl, sr, 0);//순서인덱스, 열린 왼쪽문 번호, 열린 오른쫀 문번호, 누적이동횟수
    return movecnt;
}
void InputData(){
    scanf("%d", &N);
    scanf("%d %d", &sl, &sr);
    scanf("%d", &M);
    for (int i=0; i<M; i++){
        scanf("%d", &seq[i]);
    }
}
int main(){
    InputData();
    int ans = Solve();
    printf("%d\n", ans);
    return 0;
}
 
/**************************************************************
    Problem: 2419
    User: SWT01005
    Language: C
    Result: Accepted
    Time:1 ms
    Memory:1156 kb
****************************************************************/