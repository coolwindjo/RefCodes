#include <iostream>
using namespace std;
#define MAXN ((int)5e4)
#define MAXT ((int)1e4)
int N;
int A[MAXN + 10];
int T;
int B[MAXT + 10];
void InputData(){
    cin >> N;
    for (int i=1; i<=N; i++){
        cin >> A[i];
    }
    cin >> T;
    for (int i=1; i<=T; i++){
        cin >> B[i];
    }
}
int BinarySearch(int s, int e, int d){
    while (s <= e){
        int m = (s+e)/2;
        if (A[m] == d) return m;//찾기 성공
        else if (A[m] < d) s = m+1;//s~m 찾는 데이터 없음
        else e = m-1;//e~m 찾는 데이터 없음
    }
    return 0;//없는 데이터 임
}
void Solve(){
    for (int i=1; i<=T; i++){
        cout << BinarySearch(1, N, B[i]) << endl;
    }
}
int main(){
    InputData();
    Solve();
    return 0;
}