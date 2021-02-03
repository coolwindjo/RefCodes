#include <iostream>
#define MAXN (100)
#define INF (100 * MAXN + 10)
using namespace std;
int N, M;//지하철 역수, 목적역번호
int t[MAXN+10][MAXN+10];//[출발역][도착역]=걸리는 시간
 
int visited[MAXN+10];//누적 가중치
int path[MAXN+10];//이전역
//linear queue
int que[MAXN * 100];//노드개수 * 100배
int wp, rp;
void push(int n, int t, int pre){//노드번호, 누적가중치, 이전역
    if (visited[n] <= t) return;//이전보다 좋지 않음
    visited[n] = t; path[n] = pre; que[wp++] = n;
}
int front() { return que[rp]; }
void pop() { rp++; }
bool empty() { return wp==rp; }
 
int BFS(){
    int cur;
    //1.초기화
    wp = rp = 0;
    for (int i=1; i<=N; i++){
        visited[i] = INF;
        path[i] = 0;
    }
    //2.시작위치 큐에 저장
    push(1, 0, 0);
    //3.반복문
    while(!empty()){
        cur = front(); pop();
        for (int e=1; e<=N; e++){
            push(e, visited[cur] + t[cur][e], cur);
        }
    }
    //4.결과리턴
    return visited[M];//초기값(INF) 그대로면 도착 실패임
}
void InputData(){
    cin >> N >> M;
    for (int i=1; i<=N; i++){//출발역
        for (int j=1; j<=N; j++){//도착역
            cin >> t[i][j];
        }
    }
}
void PRT(int m){
    if(m == 0) return;
    PRT(path[m]);
    cout << m << " ";
}
void OutputData(int ans){
    cout << ans << endl;
    PRT(M);
}
int main(){
    InputData();
    int ans = BFS();
    OutputData(ans);
    return 0;
}
 
/**************************************************************
    Problem: 1174
    User: SWT01005
    Language: C++
    Result: Accepted
    Time:2 ms
    Memory:2172 kb
****************************************************************/