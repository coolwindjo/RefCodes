#include <stdio.h>
#define MAXN (100)
int N;
//linear queue;
int que[MAXN * 100];
int wp, rp;
void push(int d) { que[wp++] = d; }
int front() { return que[rp]; }
int back() { return que[wp-1]; }
void pop() { rp++; }
int size() { return wp-rp; }
int empty() { return wp==rp; }
void InputData(){
    scanf("%d", &N);
}
void Solve(){
    wp = rp = 0;//큐 초기화
    //1.1~N 순서대로 큐에 저장
    for (int i=1; i<=N; i++) {
        push(i);
    }
    //2.N-1회 규칙대로 반복수행
    for (int i=0; i<N-1; i++){
        int cnt = back()/2;
        for (int k=0; k<cnt; k++){
            push(front()); pop();
        }
        printf("%d ", front()); pop();
    }
    //3.마지막 데이터 인쇄
    printf("%d\n", front()); pop();
}
int main(){
    InputData();
    Solve();
    return 0;
}
 
/**************************************************************
    Problem: 1376
    User: SWT01005
    Language: C++
    Result: Accepted
    Time:2 ms
    Memory:1196 kb
****************************************************************/

