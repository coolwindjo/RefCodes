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

constexpr int MAX_N = 20;
constexpr int MAX_U = 20;
class ProbSolv
{
    int N;
    int opened1;
    int opened2;
    int U;
    int u[MAX_U+10];
public:
    ProbSolv()
    {
        scanf("%d", &N);
        scanf("%d %d", &opened1, &opened2);
        scanf("%d", &U);
        FOR(i, U){
            scanf("%d", &u[i]);
        }
        _Solve();
    }
    ~ProbSolv(){}
private:
    void _Solve(){
        int cnt = 0;
        FOR(i, U){
            dist1 = abs(opened1 - u[i]);
            dist2 = abs(opened2 - u[i]);
            if(dist1 > dist2){
                openend1
            }
        }
    }

};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ProbSolv ps;
    return 0;
}
