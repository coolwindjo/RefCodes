#include <iostream>
#include <algorithm>
#define MAXN ((int)1e3)
using namespace std;
int N;
int A[MAXN + 10];
void InputData(){
    cin >> N;
    for (int i=0; i<N; i++){
        cin >> A[i];
    }
}
int SolveN3(){
    int cnt = 0;
    //1.연잎 오름차순 정렬
    sort(A, A+N);
    //2.경우의 수 찾기(순차탐색)
    for (int a=0; a<N-2; a++){//첫번째 연잎 인덱스
        for (int b=a+1; b<N-1; b++){//두번째 연잎 인덱스
            int first = A[b] - A[a];//첫번째 뛴 거리
            for (int c=b+1; c<N; c++){//세번째 연잎 인덱스
                int second = A[c] - A[b];//두번째 뛴 거리
                //if ((first <= second) && (second <= 2*first)) cnt++;
                if(second < first) continue;
                if(second > 2*first) break;
                cnt++;
            }
        }
    }
    return cnt;
}
int bslow(int s, int e, int d){//d값보다 크거나 같은 값중에 제일 작은 인덱스
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
int bsup(int s, int e , int d){//d값보다 작거나 같은 값중에 제일 큰 인덱스
    int sol=-1;
    while(s <= e){
        int m=(s+e)/2;
        if (A[m] <= d){
            sol=m; s=m+1;
        }
        else{
            e=m-1;
        }
    }
    return sol;
}
int Solve(){//O(N^2 logN)
    int cnt = 0;
    //1.연잎 오름차순 정렬
    sort(A, A+N);
    //2.경우의 수 찾기(이진탐색 lower & upper)
    for (int a=0; a<N-2; a++){//첫번째 연잎 인덱스
        for (int b=a+1; b<N-1; b++){//두번째 연잎 인덱스
            int first = A[b] - A[a];//첫번째 뛴 거리
            int low = bslow(0, N-1, A[b]+first);
            if (low < 0) break;
            cnt += bsup(0, N-1, A[b]+2*first) - low + 1;
        }
    }
    return cnt;
}
int main(){
    InputData();
    //int ans = SolveN3();
    int ans = Solve();
    cout << ans << endl;
    return 0;
}