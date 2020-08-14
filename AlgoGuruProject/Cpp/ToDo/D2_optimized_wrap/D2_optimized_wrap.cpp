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

constexpr int MAX_N = 5e3;
class ProbSolv
{
    int N;
    vector<int> viCand;
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
            int ni;
            scanf("%d", &ni);
            viCand.push_back(ni);
        }
        sort(viCand.begin(), viCand.end());
#ifdef TEST
        FOR(t, N){
            cout << viCand[t] << " ";
        }
        cout <<endl;
#endif
        int cost = 0;
        FOR(i, N-1){
            viCand[i+1] += viCand[i];
            cost += viCand[i+1];
#ifdef TEST
            FOR(t, N){
                cout << viCand[t] << " ";
            }
            cout <<endl;
#endif
            sort(viCand.begin()+i, viCand.end());
        }
        cout << cost;
    }

};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifdef TEST
    int numTCs = 2;
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
