#include <iostream>
using namespace std;
int N, M;//던진횟수, 출력모양
int dice[5];
int used[6+1];
void InputData(){
    cin >> N >> M;
}
void DFS1(int n){
    if (n >= N){//종료조건
        for (int i=0; i<N; i++){
            cout << dice[i] << " ";
        }
        cout << endl;
        return;
    }
    for (int i=1; i<=6; i++){
        dice[n]=i;
        DFS1(n+1);
    }
}
void DFS2(int n, int s){
    if (n >= N){//종료조건
        for (int i=0; i<N; i++){
            cout << dice[i] << " ";
        }
        cout << endl;
        return;
    }
    for (int i=s; i<=6; i++){
        dice[n]=i;
        DFS2(n+1, i);
    }
}
void DFS3(int n){
    if (n >= N){//종료조건
        for (int i=0; i<N; i++){
            cout << dice[i] << " ";
        }
        cout << endl;
        return;
    }
    for (int i=1; i<=6; i++){
        if (used[i] == 1) continue;//이미 사용했음
        used[i]=1;//표시
        dice[n]=i;
        DFS3(n+1);
        used[i]=0;//표시제거
    }
}
void Solve(){
    if (M == 1){//중복순열
        DFS1(0);
    }
    else if (M == 2){//중복조합
        DFS2(0, 1);
    }
    else{//순열
        DFS3(0);
    }
}
int main(){
    InputData();
    Solve();
    return 0;
}
 
/**************************************************************
    Problem: 1956
    User: SWT01005
    Language: C++
    Result: Accepted
    Time:11 ms
    Memory:2084 kb
****************************************************************/