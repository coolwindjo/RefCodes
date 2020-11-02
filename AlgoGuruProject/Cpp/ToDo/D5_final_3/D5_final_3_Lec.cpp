#include <stdio.h>
#define MAXN ((int)1e4)
int N;//지방 수
int A[MAXN + 10];
int M;//총예산
void InputData(){
    scanf("%d", &N);
    for (int i=0; i<N; i++){
        scanf("%d", &A[i]);
    }
    scanf("%d", &M);
}
int isPossible(int m){//상한액이하면 그대로 배정, 초과면 상한액만 지불
    int sum = M;
    for (int i=0; i<N; i++){
        if (A[i] > m) sum -= m;
        else sum -= A[i];
        if (sum < 0) return 0;//불가능
    }
    return 1;//가능
}
int Solve(){
    int s=0, e=0, sol=0;
    //1.요청 예산 중 최대값 찾기
    for (int i=0; i<N; i++){
        if (e < A[i]) e = A[i];
    }
    //2.이진탐색으로 최대 상한액(upper bound)
    while(s <= e){
        int m = (s+e)/2;
        if (isPossible(m) == 1){//상한액으로 가능한 경우
            sol = m; s=m+1;
        }
        else{
            e=m-1;
        }
    }
    return sol;
}
int main(){
    InputData();
    int ans = Solve();
    printf("%d\n", ans);
    return 0;
}
 
/**************************************************************
    Problem: 1308
    User: SWT01005
    Language: C
    Result: Accepted
    Time:3 ms
    Memory:1196 kb
****************************************************************/