#include <iostream>
#include <algorithm>
#define MAXNM ((int)1e5)
using namespace std;
int M, N, L;//사대수, 동물수, 사거리
int A[MAXNM + 10];//사대 좌표
int X[MAXNM + 10];//동물 가로 좌표
int Y[MAXNM + 10];//동물 세로 좌표
void InputData(){
    cin >> M >> N >> L;
    for (int i=0; i<M; i++){//사대
        cin >> A[i];
    }
    for (int i=0; i<N; i++){//동물
        cin >> X[i] >> Y[i];
    }
}
int bslow(int s, int e, int d){//d보다 크거나 같은 값 중에 제일 작은 인덱스
    int sol=-1;
    while(s <= e){
        int m=(s+e)/2;
        if (A[m] >= d){
            sol=m; e=m-1;
        }
        else{
            s=m+1;
        }
    }
    return sol;
}
int Solve(){
    int cnt = 0;
    //1.사대를 오름차순으로 정렬
    sort(A, A+M);
    //2.동물 기준으로 잡을 수 있는 사대 존재 여부 파악
    for (int i=0; i<N; i++){//동물 인덱스
        if (Y[i] > L) continue;//무조건 못 잡음, skip
        int low = X[i] + Y[i] - L;
        int up = L + X[i] - Y[i];
        int idx = bslow(0, M-1, low);
        if ((idx < 0) || (A[idx] > up)) continue;//잡을 수 있는 사대 없음, skip
        cnt++;
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
    Problem: 1231
    User: SWT01005
    Language: C++
    Result: Accepted
    Time:87 ms
    Memory:3256 kb
****************************************************************/