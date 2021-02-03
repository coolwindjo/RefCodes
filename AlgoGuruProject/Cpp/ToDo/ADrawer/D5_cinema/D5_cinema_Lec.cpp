#include <iostream>
#include <algorithm>
using namespace std;
#define MAXN ((int)1e5)
int N;
struct DATA{
    int s, e;
};
DATA A[MAXN + 10];
void InputData(){
    cin >> N;
    for (int i=0; i<N; i++){
        cin >> A[i].s >> A[i].e;
    }
}
bool comp(DATA a, DATA b){ return a.e < b.e; }
int Solve(){
    //1.종료시간 기준 오름차순 정렬
    sort(A, A+N, comp);
    //2.볼수있는 영화 개수 계산
    int cnt = 1;
    int e = A[0].e;
    for (int i=1; i<N; i++){
        if (e >= A[i].s) continue;//시간 겹쳐서 볼수없음
        cnt++;
        e = A[i].e;
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
    Problem: 1237
    User: SWT01005
    Language: C++
    Result: Accepted
    Time:66 ms
    Memory:2872 kb
****************************************************************/