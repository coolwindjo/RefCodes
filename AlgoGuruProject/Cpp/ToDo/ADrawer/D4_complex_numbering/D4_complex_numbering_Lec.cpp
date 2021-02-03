#include <iostream>
#include <algorithm>
#define MAXN (25)
using namespace std;
int N;//지도크기
char map[MAXN+5][MAXN+5];
int visited[MAXN+5][MAXN+5];
int house;//단지내 집수 파악 용도
int sol[MAXN*MAXN];//단지내 집수 저장
int dh[] = {-1, 1, 0, 0};
int dw[] = {0, 0, -1, 1};
void FloodFill(int h, int w){
    if (map[h][w] != '1') return;
    if (visited[h][w] == 1) return;
    visited[h][w]=1; house++;
    for (int i=0; i<4; i++){
        FloodFill(h+dh[i], w+dw[i]);
    }
}
int Solve(){
    int cnt=0;
    for (int i=1; i<=N; i++){
        for (int j=1; j<=N; j++){
            if (map[i][j] != '1') continue;//집 아니므로 skip
            if (visited[i][j] == 1) continue;//이미 방문했음, 다른 단지에 포함된 집, skip
            house = 0;
            FloodFill(i, j);
            sol[cnt++] = house;
        }
    }
    return cnt;
}
void InputData(){
    cin >> N;
    for (int i=1; i<=N; i++){
        cin >> &map[i][1];
    }
}
void OutputData(int cnt){
    cout << cnt << endl;
    sort(sol, sol+cnt);//오름차순 정렬
    for (int i=0; i<cnt; i++){
        cout << sol[i] << endl;
    }
}
int main(){
    InputData();
    int ans = Solve();
    OutputData(ans);
    return 0;
}
 
/**************************************************************
    Problem: 1148
    User: SWT01005
    Language: C++
    Result: Accepted
    Time:2 ms
    Memory:2096 kb
****************************************************************/