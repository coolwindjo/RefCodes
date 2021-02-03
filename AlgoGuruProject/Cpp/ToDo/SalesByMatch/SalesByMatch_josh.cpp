#if 1
#define TEST
#endif // 1

/*
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
/*/ 
#include "../../ProbSolvStart.h"
//*/

constexpr int maxN = 101;

class ProbSolv
{
    int n;
    vi ar;
public:
    ProbSolv()
    {
        n = 0;
        cin >> n;
        FOR (i, n) {
            int color = 0;
            cin >> color;
            ar.push_back(color);
        }
        _Solve();
    }
    ~ProbSolv(){}
private:
    void _Solve(){
        sort(ar.begin(), ar.end());
        int pCnt = 0;
        int f = ar[0];
        FOR_INC (i, 1, n) {
            if (ar[i] == f) {   // paired
               pCnt++; 
               f = -1;
            }
            else {              // new color
                f = ar[i];
            }
        }

        cout << pCnt;
    }

};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#if 0
    int numTCs = 0;
    cin >> numTCs;
    FOR(tc, numTCs){
        cout << "#" << tc+1 <<" ";
#endif
        ProbSolv ps;
#if 0
        cout << endl;
    }
#endif
    return 0;
}
