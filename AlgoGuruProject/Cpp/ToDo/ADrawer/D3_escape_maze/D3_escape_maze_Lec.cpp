#include <iostream>
using namespace std;
#define MAXN (100)
int W, H;//미로 가로, 세로 크기
int sw, sh, ew, eh;//출발 가로세로, 도착 가로세로 좌표
char map[MAXN + 10][MAXN + 10];//미로정보
 
int visited[MAXN + 10][MAXN + 10];//경험표시용(중복경복 방지용)
//linear queue
typedef struct{
    int h, w, t;//세로, 가로, 시간
}QUE;
QUE que[MAXN * MAXN + 10];//중복방문 하지 않으므로 경험개수(visited 요소개수만큼) 확보
int wp, rp;
void push(int h, int w, int t){
    //if ((h<1) || (h>H) || (w<1) || (w>W)) return;//범위 벗어남(이 문제에서는 필요없음)
    if (map[h][w] != '0') return;//범위를 벗어났거나 벽임
    if (visited[h][w] == 1) return;//이미 방문했음(이미 경험했음)
    visited[h][w]=1;//방문표시(경험표시)
    que[wp].h=h; que[wp].w=w; que[wp].t=t; wp++;
}
QUE front() { return que[rp]; }
void pop() { rp++; }
bool empty() { return wp==rp; }
int BFS(){
    int dh[] = {-1, 1, 0, 0};
    int dw[] = {0, 0, -1, 1};
    QUE cur;
    //1.초기화
    wp = rp = 0;//큐 초기화
    //필요시 visited 초기화
    //2.시작위치 큐에 저장
    push(sh, sw, 0);
    //3.반복문
    while(!empty()){
        cur = front(); pop();
        if ((cur.h==eh) && (cur.w == ew)) return cur.t;//도착 성공
        for (int i=0; i<4; i++){
            push(cur.h+dh[i], cur.w+dw[i], cur.t+1);
        }
    }
    //4.실패(이 문제는 이런 경우 없음)
    return -1;//디버깅을 위해....
}
void InputData(){
    cin >> W >> H;//scanf("%d %d", &W, &H);
    cin >> sw >> sh >> ew >> eh;//scanf("%d %d %d %d", &sw, &sh, &ew, &eh);
    for (int i=1; i<=H; i++){//세로 인덱스
        cin >> &map[i][1]; //scanf("%s", &map[i][1]);
    }
}
int main(){
    InputData();
    int ans = BFS();
    cout << ans << endl;
    return 0;
}
 
/**************************************************************
    Problem: 1155
    User: SWT01005
    Language: C++
    Result: Accepted
    Time:1 ms
    Memory:2260 kb
****************************************************************/