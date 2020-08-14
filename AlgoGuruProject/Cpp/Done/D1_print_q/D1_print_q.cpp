#include "../../ProbSolvStart.h"

constexpr int MAX = (int)1e4;

struct doc_prio
{
    int docN;
    int prioN;
};

class ProbSolv
{
    int N;
    int M;
    doc_prio Q[MAX + 10];
    int P[10];
    int wp, rp;
public:
    ProbSolv()
    {
        _Solve();
    }
    ~ProbSolv(){}
private:
    void _Solve(){
        wp = rp = 0;
        FOR(i, 10){
            P[i] = 0;
        }
        scanf("%d", &N);
        scanf("%d", &M);
        FOR(i, N){
            int prioN = 0;
            scanf("%d", &prioN);
            P[prioN]++;
            _EnQ(doc_prio{i, prioN});
        }
        int cnt = 0;
        while(_Empty()==false){
            doc_prio dp = _Front(); _DeQ();
            if (_Highest(dp.prioN) == true) {
                P[dp.prioN]--;
                cnt++;
                if (dp.docN == M){
                    cout << cnt;
                    break;
                }
            }
            else {
                _EnQ(dp);
            }
        }
    }
    bool _Highest(int prioN){
        FOR_DEC(i, prioN+1, 10){
            if (P[i] >= 1) return false;
        }
        return true;
    }
    void _EnQ(doc_prio dp){
        if (W_IFNOT(wp < MAX)){
            Q[wp++] = dp;
        }
    }
    doc_prio _Front(){
        W_IFNOT(wp > rp);
        return Q[rp];
    }
    doc_prio _Back(){
        if (W_IFNOT(wp > rp)) return Q[wp-1];
    }
    void _DeQ(){ rp++; }
    int _Size(){
        W_IFNOT(wp >= rp);
        return wp-rp;
    }
    bool _Empty(){ return wp == rp; }
};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int numTCs = 0;
    scanf("%d", &numTCs);
    FOR(tc, numTCs){
        ProbSolv ps;
        cout << endl;
    }
    return 0;
}
