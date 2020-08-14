#include "../../ProbSolvStart.h"

constexpr int MAX = (int)1e4;

class ProbSolv
{
    int N;
    int Q[MAX + 10];
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
        scanf("%d", &N);
        FOR(i, N){
            _EnQ(i+1);
        }
        while(_Empty()==false){
            int numMoves = 0;
            numMoves = (int)(_Back() * 0.5);
            FOR(i, numMoves){
                _EnQ(_Front()); _DeQ();
            }
            cout << _Front() <<endl; _DeQ();
        }
    }
    void _EnQ(int d){
        if (W_IFNOT(wp < MAX)){
            Q[wp++] = d;
        }
    }
    int _Front(){
        W_IFNOT(wp > rp);
        return Q[rp];
    }
    int _Back(){
        if (W_IFNOT(wp > rp)) return Q[wp-1];
        return -1;
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

    ProbSolv ps;
    return 0;
}
