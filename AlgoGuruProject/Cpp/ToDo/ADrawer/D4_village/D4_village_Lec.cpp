#include <iostream>
#define MAXN (100)
using namespace std;
int N;//마을 크기
char map[MAXN+10][MAXN+10];//지도정보
int dh[] = {-1, -1, -1, 0, 1, 1,  1,  0};
int dw[] = {-1,  0,  1, 1, 1, 0, -1, -1};
void InputData(){
    cin >> N;
    for (int i=1; i<=N; i++){
        cin >> &map[i][1];
    }
}
void FloodFill(int h, int w){
    if (map[h][w] != '1') return;//호수 아님(범위 체크 겸용임)
    map[h][w] = 0;//호수 아닌걸로 표시
    for (int i=0; i<8; i++){
        FloodFill(h+dh[i], w+dw[i]);
    }
}
int Solve(){
    int cnt = 0;
    for (int i=1; i<=N; i++){
        for (int j=1; j<=N; j++){
            if (map[i][j] != '1') continue;//호수 아님, skip
            cnt++;
            FloodFill(i, j);//연결된 호수 찾아다니며 표시하기
        }
    }
    return cnt;
}
int main(){
    InputData();
    int ans = Solve();
    cout << ans << endl;
    return 0;
}
 
/**************************************************************
    Problem: 1240
    User: SWT01005
    Language: C++
    Result: Accepted
    Time:3 ms
    Memory:2440 kb
****************************************************************/