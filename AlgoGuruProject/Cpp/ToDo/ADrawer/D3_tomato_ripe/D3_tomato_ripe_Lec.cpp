#include <iostream>
using namespace std;
#define MAXN ((int)1e3)
int W, H;//상자 가로 세로 크기
int map[MAXN + 10][MAXN + 10];//0:익지 않은 토마토, 1:익은 토마토, -1:빈칸
int tomato;//익지 않은 토마토 개수
//linear queue;
struct QUE{
    int h, w, t;//세로, 가로, 시간
};
QUE que[MAXN * MAXN + 10];
int wp, rp;
void push(int h, int w, int t){
    if ((h<0)||(h>=H)||(w<0)||(w>=W)) return;//범위 벗어남
    if (map[h][w] != 0) return;//안 익은 토마토 아님(익은 토마토 or 빈칸)
    map[h][w] = 1; tomato--;
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
    wp = rp = 0;
    //2.시작위치 큐에 저장
    tomato = H * W;
    for (int i=0; i<H; i++){
        for (int j=0; j<W; j++){
            if (map[i][j] == 1){//익은 토마토(시작 위치)
                map[i][j] = 0;
                push(i, j, 0);
            }
            else if(map[i][j] == -1){//빈칸
                tomato--;
            }
        }
    }
    if (tomato == 0) return 0;//안 익은 토마토 없음
    //3.반복문
    while(!empty()){
        cur = front(); pop();
        for (int i=0; i<4; i++){
            push(cur.h+dh[i], cur.w+dw[i], cur.t+1);
            if (tomato == 0) return cur.t+1;//성공, 모든 토마토 익음
        }
    }
    //4.실패(모든 토마토를 익히지 못했음)
    return -1;
}
void InputData(){
    cin >> W >> H;
    for (int i=0; i<H; i++){//세로 인덱스
        for (int j=0; j<W; j++){//가로 인덱스
            cin >> map[i][j];
        }
    }
}
int main(){
    InputData();
    int ans = BFS();
    cout << ans << endl;
    return 0;
}
 
/**************************************************************
    Problem: 1156
    User: SWT01005
    Language: C++
    Result: Accepted
    Time:150 ms
    Memory:17788 kb
****************************************************************/