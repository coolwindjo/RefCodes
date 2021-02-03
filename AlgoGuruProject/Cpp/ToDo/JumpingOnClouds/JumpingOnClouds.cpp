#if 1
#define TEST
#endif // 1

#include "../../ProbSolvStart.h"

constexpr int MAX_N = 100 + 1;

class ProbSolv
{
    int n;
    vi viC;
public:
    ProbSolv()
    {
        cin >> n;

        FOR(i, n){
            int zeroOrOne;
            cin >> zeroOrOne;
            viC.push_back(zeroOrOne);
        }

        W_IFNOT(viC[0] == 0);
        W_IFNOT(viC[n-1] == 0);

        _Solve();
    }
    ~ProbSolv(){}
private:
    void _Solve(){
        int jCnt = 0;
        int last = 0;
        FOR(i, n+1){
            bool isThunder = (viC[i] == 1);
            if (isThunder || (i == n)) {
                if (isThunder) jCnt++;
                int gap = (i-1) - last;
                last = i+1;
                if (gap > 0) {
                    jCnt += ((gap+1)/2);
                }
            }
        }
        cout << jCnt;
    }
};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int numTCs = 0;
    cin >> numTCs;
    FOR (tc, numTCs) {
        cout << "#" << tc+1 <<" ";
        ProbSolv ps;
        cout << endl;
    }
    return 0;
}
