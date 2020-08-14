#if 0
#define TEST
#endif // 1

#include <bits/stdc++.h>
using namespace std;

#define FOR_INC(i, from, to) for(int (i)=(from); (i)<(to); ++(i))
#define FOR_DEC(i, from, to) for(int (i)=(to)-1; (i)>=(from); --(i))
#define FOR(i, to) FOR_INC((i), 0, (to))
#define OOR(x, min, max) (((x) < (min) || (x) > (max)))

static const int WarnIfNot(const int condFlag, const char* condition){
 	if (condFlag == 0) {
        cout << "Warning: [" << condition << "] is violated!\n";
    }
    return condFlag;
}
#define W_IFNOT(cond) WarnIfNot((cond), (#cond))
#define P_IFNOT(cond, var) if (!W_IFNOT(cond)) cout << "= " << var <<endl;
// #include "../../ProbSolvStart.h"

int Box[] = {1, 5, 10, 50, 100, 500, 1000, 3000, 6000, 12000};
constexpr int MAX_BOX_KIND = sizeof(Box)/sizeof(int);

class ProbSolv
{
    int N;//보내려는 물품 개수
    int C[MAX_BOX_KIND];//BOX 개수(1, 5, 10, 50, 100, 500, 1000, 3000, 6000, 12000 순)
    int sol[MAX_BOX_KIND];//보내는 BOX 개수
public:
    ProbSolv()
    {
        scanf("%d", &N);
        FOR(i, MAX_BOX_KIND){
            scanf("%d", &C[i]);
            sol[i] = 0;
        }
        _Solve_WrongAnswer();
        // _Solve();
        int ans = 0;
        FOR(i, MAX_BOX_KIND){
            ans += sol[i];
        }
        OutputData(ans);
    }
    ~ProbSolv(){}
private:
    void _Solve(){
        int totalN = 0;
        FOR(i, MAX_BOX_KIND){
            total += C[i] * Box[i];
        }
        int remN = totalN - N;
        int remBoxCnt = 0;
        FOR_DEC(i, 0, MAX_BOX_KIND){
            int boxCnt += remN/Box[i];
            if(boxCnt > C[i]){
                boxCnt = C[i];
            }
            remN -= boxCnt*Box[i];
            sol[i] = C[i] - boxCnt;
            remBoxCnt += boxCnt;
        }
    }
    void _Solve_WrongAnswer(){
        FOR(i, MAX_BOX_KIND){
            int factor = N/Box[i];
            if(factor < 1) break;
            if(factor < C[i]){
                sol[i] = factor;
            }
            else{
                int rem = (factor-C[i])%(Box[i+1]/Box[i]);
                sol[i] = C[i] - (Box[i+1]/Box[i] - rem);
            }
            N = N - (sol[i] * Box[i]);
        }

    }
    void OutputData(int ans){
        int i;
        cout << ans << endl;
        for(i = 0; i < 10; i++){
            cout << sol[i] << " ";
        }
        cout << endl;
    }
};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifdef TEST
    int numTCs = 3;
    FOR(tc, numTCs){
        cout << "#" << tc+1 <<" ";
#endif
        ProbSolv ps;
#ifdef TEST
        cout << endl;
    }
#endif
    return 0;
}
