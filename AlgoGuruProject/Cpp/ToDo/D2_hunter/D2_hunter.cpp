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

constexpr int MAX_M = 1e5;
constexpr int MAX_N = 1e5;
constexpr int MAX_L = 1e9;

struct Pt
{
    int x;
    int y;
};

class ProbSolv
{
    int M;
    int N;
    int mx[MAX_M + 10];
    Pt anm[MAX_N + 10];
    int L;
public:
    ProbSolv()
    {
        _Solve();
    }
    ~ProbSolv(){}
private:
    void _Solve(){
        scanf("%d", &M);
        scanf("%d", &N);
        scanf("%d", &L);
        FOR(i, M){
            scanf("%d", &mx[i]);
        }
        FOR(i, N){
            scanf("%d %d", &anm[i].x, &anm[i].y);
        }

    }
};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifdef TEST
    int numTCs = 0;
    cin >> numTCs;
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
