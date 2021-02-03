#include <iostream>
using namespace std;
#define MAXN ((int)1e4)
int N;//실수개수
double A[MAXN + 10];//실수
void InputData(){
    cin >> N;
    for (int i=0; i<N; i++){
        cin >> A[i];
    }
}
double SolveN3(){
    double mul, maxv=0;
    for (int s=0; s<N; s++){//시작 인덱스
        for (int e=s; e<N; e++){//끝 인덱스
            mul = 1;
            for (int k=s; k<=e; k++){//s~e 곱셈
                mul *= A[k];
            }
            if (maxv < mul) maxv = mul;
        }
    }
    return maxv;
}
double SolveN2(){
    double mul, maxv=0;
    for (int s=0; s<N; s++){//시작 인덱스
        mul = 1;
        for (int k=s; k<N; k++){//s~N 곱셈
            mul *= A[k];
            if (maxv < mul) maxv = mul;
        }
    }
    return maxv;
}
double Solve(){
    double mul = 1, maxv = 0;
    for (int i=0; i<N; i++){
        if (mul > 1) mul *= A[i];//기존 곱셈 결과가 1초과면 계속 곱해가는게 이득
        else mul = A[i];//1이하면 새로 시작하는게 이득
        if (maxv < mul) maxv = mul;
    }
    return maxv;
}
int main(){
    InputData();
    //double ans = SolveN3();
    //double ans = SolveN2();
    double ans = Solve();
    printf("%.3f\n", ans);
    return 0;
}
 
/**************************************************************
    Problem: 1068
    User: SWT01005
    Language: C++
    Result: Accepted
    Time:3 ms
    Memory:2164 kb
****************************************************************/