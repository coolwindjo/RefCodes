#include <iostream>
#include <stdio.h>
#define MAXN (128)
#define INF ((int)1e5)
int dist[MAXN][MAXN];//노드간에 거리
int visited[MAXN];
//linear queue
char que[MAXN * 100];
int wp, rp;
void push(char n, int t){
    if (visited[n] <= t) return;
    visited[n]=t; que[wp++]=n;
}
char front() { return que[rp]; }
void pop() { rp++; }
bool empty() { return wp==rp; }
char BFS(){
    char cur;
    //1.초기화
    wp = rp = 0;
    for (char i='A'; i<='z'; i++) visited[i]=INF;
    //2.시작위치 큐에 저장
    push('Z', 0);
    //3.반복문
    while(!empty()){
        cur = front(); pop();
        for (char e='A'; e<='z'; e++){
            if (dist[cur][e] == 0) continue;//연결된 길 없음
            push(e, visited[cur]+dist[cur][e]);
        }
    }
    //4.결과리턴
    char idx='A';
    for (char e='B'; e<='Y'; e++){
        if (visited[idx] > visited[e]) idx = e;
    }
    return idx;
}
void InputData(){
    int P, d; char s, e;
    scanf("%d", &P);
    for (int i=0; i<P; i++){
        scanf(" %c %c %d", &s, &e, &d);
        if ((dist[s][e] == 0) || (dist[s][e] > d)){
            dist[s][e] = dist[e][s] = d;
        }
    }
}
int main(){
    InputData();
    char ans = BFS();
    printf("%c %d\n", ans, visited[ans]);
    return 0;
}
 
/**************************************************************
    Problem: 1176
    User: SWT01005
    Language: C++
    Result: Accepted
    Time:3 ms
    Memory:2164 kb
****************************************************************/