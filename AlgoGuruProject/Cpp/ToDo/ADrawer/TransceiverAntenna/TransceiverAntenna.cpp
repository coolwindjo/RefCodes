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

typedef vector<int> vi;
// #include "../../ProbSolvStart.h"

constexpr int MAX_N = 1e5;

class ProbSolv
{
    int N;
    int H[MAX_N + 10];
    vi viSt;
public:
    ProbSolv()
    {
        _Solve();
    }
    ~ProbSolv(){}
private:
    void _Solve(){
        scanf("%d", &N);
        FOR(i, N){
            scanf("%d", &H[i]);
        }
        int transCnt = 0;
        FOR(i, N){
        }
        cout << transCnt;
    }
    void _Solve_WrongAnswer(){
        scanf("%d", &N);
        FOR(i, N){
            scanf("%d", &H[i]);
        }
        int transCnt = N-1;
        bool justBefore = false;
        FOR(i, N){
            while (!viSt.empty()){
                if (viSt.back() > H[i]) break;
                if (justBefore == false) {
                    transCnt++;
                }
                else {
                    justBefore = false;
                }
                viSt.pop_back();
            }

            viSt.push_back(H[i]);
            justBefore = true;
        }
        cout << transCnt;
    }
};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ProbSolv ps;
    return 0;
}