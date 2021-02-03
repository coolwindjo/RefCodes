
#include <iostream>
#include <algorithm>
#define MAXN ((int)5e3)
using namespace std;
int N;//포장개수
int A[MAXN + 10];//사탕개수
void InputData(){
    cin >> N;
    for (int i=0; i<N; i++){
        cin >> A[i];
    }
}
int simplesort(int s, int e){//최소값 2개만 정렬
    for (int i=s; i<s+2; i++){
        for (int j=i+1; j<=e; j++){
            if (A[i] > A[j]){
                int tmp=A[i]; A[i]=A[j]; A[j]=tmp;
            }
        }
    }
}
int Solve(){
    int sum = 0;
    for (int i=0; i<N-1; i++){
        //sort(&A[i], A+N);
        simplesort(i, N-1);
        A[i+1] += A[i];//제일 작은 두개 포장 합치기
        sum += A[i+1];//비용 누적 더하기
    }
    return sum;
}
int main(){
    InputData();
    int ans = Solve();
    cout << ans << endl;
    return 0;
}
 