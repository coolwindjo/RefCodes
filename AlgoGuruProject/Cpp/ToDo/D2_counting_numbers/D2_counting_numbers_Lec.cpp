#include <iostream>
using namespace std;
#define MAXN ((int)2e5)
#define MAXM ((int)2e5)
int N;
int A[MAXN + 10];
int M;
int B[MAXM + 10];
void InputData(){
    cin >> N;
    for (int i=0; i<N; i++){
        cin >> A[i];
    }
    cin >> M;
    for (int i=0; i<M; i++){
        cin >> B[i];
    }
}
int BSlow(int s, int e, int d){//d값과 같은 인덱스 중에 제일 작은 인덱스 찾기
    int sol = -1;
    while(s <= e){
        int m = (s+e)/2;
        if (A[m] == d){
            sol = m; e=m-1;
        }
        else if(A[m] < d) s=m+1;
        else e=m-1;
    }
    return sol;
}
int BSup(int s, int e, int d){//d값과 같은 인덱스 중에 제일 큰 인덱스 찾기
    int sol = -1;
    while(s <= e){
        int m = (s+e)/2;
        if (A[m] == d){
            sol = m; s=m+1;
        }
        else if(A[m] < d) s=m+1;
        else e=m-1;
    }
    return sol;
}
void Solve(){
    for(int i=0; i<M; i++){
        int cnt = 0;
        int low = BSlow(0, N-1, B[i]);
        if (low >= 0){
            cnt = BSup(0, N-1, B[i]) - low + 1;
        }
        cout << cnt << " ";
    }
}
int main(){
    InputData();
    Solve();
    return 0;
}