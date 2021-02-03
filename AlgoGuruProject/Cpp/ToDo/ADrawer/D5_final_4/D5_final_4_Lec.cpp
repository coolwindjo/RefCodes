#include <stdio.h>
#define MAXN (102)
#define INF (50 * 50 * MAXN * MAXN)
int N;//산크기
int eh, ew;//정상 위치 세로, 가로
int map[MAXN][MAXN];
int visited[MAXN][MAXN];//누적가중치
//linear queue
typedef struct{
    int h, w;
}QUE;
QUE que[MAXN * MAXN * 50];
int wp, rp;
void push(int h, int w, int t){
    if (visited[h][w] <= t) return;
    visited[h][w]=t;
    que[wp].h=h; que[wp].w=w; wp++;
}
QUE front() { return que[rp]; }
void pop() { rp++; }
int empty() { return wp==rp; }
int BFS(){
    int dh[] = {-1, 1, 0, 0};
    int dw[] = {0, 0, -1, 1};
    //1.초기화
    wp = rp = 0;
    for (int h=0; h<=N+1; h++){
        for (int w=0; w<=N+1; w++){
            visited[h][w]=INF;
        }
    }
    //2.시작위치 큐에 저장
    push(0, 0, 0);
    //3.반복문
    while(!empty()){
        QUE cur = front(); pop();
        for (int i=0; i<4; i++){
            int nh = cur.h+dh[i];
            int nw = cur.w+dw[i];
            if ((nh<0)||(nh>N+1)||(nw<0)||(nw>N+1)) continue;//범위 벗어남
            int power = map[cur.h][cur.w] - map[nh][nw];//현재 격자 높이  - 갈곳 격자 높이
            if (power < 0) power *= power;//음수면 오르막길이므로 제곱
            push(nh, nw, visited[cur.h][cur.w]+power);
        }
    }
    //4.결과
    return visited[eh][ew];
}
void InputData(){
    scanf("%d", &N);
    scanf("%d %d", &eh, &ew);
    for (int h=1; h<=N; h++){
        for (int w=1; w<=N; w++){
            scanf("%d", &map[h][w]);
        }
    }
}
int main(){
    InputData();
    int ans = BFS();
    printf("%d\n", ans);
    return 0;
}
 
/**************************************************************
    Problem: 1178
    User: SWT01005
    Language: C
    Result: Accepted
    Time:13 ms
    Memory:5300 kb
****************************************************************/