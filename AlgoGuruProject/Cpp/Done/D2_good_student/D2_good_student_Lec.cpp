#include <iostream>
#include <algorithm>
#define MAXN ((int)3e4)
using namespace std;
int N;//학생수
struct DATA{
    int id, score;
};
DATA A[MAXN + 10];
void InputData(){
    cin >> N;
    for (int i=1; i<=N; i++){
        cin >> A[i].score;
        A[i].id = i;
    }
}
void OutputData(){
    for (int i=1; i<=3; i++){
        cout << A[i].id << " ";
    }
}
bool comp(DATA a, DATA b){//성적 내림차순, 아이디 오름차순
    if (a.score == b.score) return a.id < b.id;
    return a.score > b.score;
}
int main(){
    InputData();
    sort(&A[1], &A[N+1], comp);
    OutputData();
    return 0;
}
 
/**************************************************************
    Problem: 1439
    User: SWT01005
    Language: C++
    Result: Accepted
    Time:14 ms
    Memory:2324 kb
****************************************************************/
