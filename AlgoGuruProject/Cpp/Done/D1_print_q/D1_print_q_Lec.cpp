#include <stdio.h>
#define MAXN (100)
int N, M;//문서수, 궁금한 문서번호
int priocnt[10];//우선순위별 개수
//linear queue
struct QUE{
    int p, idx;//우선순위, 문서번호
};
QUE que[MAXN * 100];
int wp, rp;
void push(int p, int idx){
    que[wp].p=p; que[wp].idx=idx; wp++;
}
QUE front() { return que[rp]; }
void pop() { rp++; }
int empty() { return wp==rp; }
int Solve(){
    int seq = 0;
    for (int i = 9; i>= 1; i--){//우선순위 9순위 부터
        while(priocnt[i]){
            QUE cur = front();  pop();
            if (cur.p == i){//가장 높은 우선순위 임, 인쇄
                seq++;
                if (cur.idx == M) return seq;//궁금한 문서임
                priocnt[i]--;
            }
            else{
                push(cur.p, cur.idx);
            }
        }
    }
}
void InputData(){
    int p;
    scanf("%d %d", &N, &M);
 
    wp = rp = 0;//큐 초기화
    for (int i=1; i<=9; i++) priocnt[i]=0;//초기화
 
    for (int i=0; i<N; i++){
        scanf("%d", &p);
        push(p, i);
        priocnt[p]++;
    }
}
int main(){
    int T, t;
    scanf("%d", &T);
    for (t=1; t<=T; t++){
        InputData();
        int ans = Solve();
        printf("%d\n", ans);
    }
    return 0;
}
 
/**************************************************************
    Problem: 2679
    User: SWT01005
    Language: C++
    Result: Accepted
    Time:1 ms
    Memory:1236 kb
****************************************************************/