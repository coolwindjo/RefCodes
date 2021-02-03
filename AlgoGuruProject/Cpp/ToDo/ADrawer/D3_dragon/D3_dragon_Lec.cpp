#include <iostream>
#include <string.h>
#define MAXN (30)
using namespace std;
int L, R, C;//층, 세로, 가로 크기
char map[MAXN+2][MAXN+2][MAXN+2];//[층][세로][가로]
int visited[MAXN+2][MAXN+2][MAXN+2];
//linear queue
struct QUE{
    int l, r, c, t;//층, 세로, 가로, 시간
};
QUE que[MAXN * MAXN * MAXN + 10];
int wp, rp;
bool push(int l, int r, int c, int t){
    if (map[l][r][c] == 'E') return true;//도착 성공
    if (map[l][r][c] != '.') return false;//길이 아니므로
    if (visited[l][r][c] == 1) return false;//이미 방문 했음
    visited[l][r][c]=1;
    que[wp].l=l; que[wp].r=r; que[wp].c=c; que[wp].t=t; wp++;
    return false;//도착 안했음
}
QUE front() { return que[rp]; }
void pop() { rp++; }
bool empty() { return wp==rp; }
int BFS(){
    int dl[] = {0, 0, 0, 0, -1, 1};
    int dr[] = {-1, 1, 0, 0, 0, 0};
    int dc[] = {0, 0, -1, 1, 0, 0};
    QUE cur;
    //1.초기화
    wp = rp = 0;//큐 초기화
    memset(visited, 0, sizeof(visited));
    //2.시작위치 큐에 저장
    for (int i=1; i<=L; i++){
        for (int j=1; j<=R; j++){
            for (int k=1; k<=C; k++){
                if (map[i][j][k] == 'S'){
                    map[i][j][k] = '.';
                    push(i, j, k, 0);
                    goto EXIT;
                }
            }
        }
    }
EXIT:
    //3.반복문
    while(!empty()){
        cur = front(); pop();
        for (int i=0; i<6; i++){
            if (push(cur.l+dl[i], cur.r+dr[i], cur.c+dc[i], cur.t+1)) return cur.t+1;
        }
    }
    //4.실패
    return -1;
}
bool InputData(){
    cin >> L >> R >> C;
    if ((L == 0) && (R == 0) && (C == 0)) return false;
    memset(map, 0, sizeof(map));//테스트 케이스 여러개면 초기화 필요
    for (int i=1; i<=L; i++) {//층 인덱스
        for (int j=1; j<=R; j++){//세로 인덱스
            cin >> &map[i][j][1];
        }
    }
    return true;
}
void DebugPRT(){
    for (int i=1; i<=L; i++){
        for (int j=1; j<=R; j++){
            cout << &map[i][j][1] << endl;
        }
    }
}
int main(){
    for(;;){
        if (!InputData()) break;
        //DebugPRT();
        int ans = BFS();
        if (ans == -1) cout << "Trapped!" << endl;
        else cout << "Escaped in " << ans << " minute(s)." << endl;
    }
    return 0;
}
 
/**************************************************************
    Problem: 3347
    User: SWT01005
    Language: C++
    Result: Accepted
    Time:7 ms
    Memory:2668 kb
****************************************************************/