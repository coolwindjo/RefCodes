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

// const int MAX = 10000 + 10;
constexpr int MAX = (int)1e4;

class ProbSolvLec
{
    int N;
    int Q[MAX];
    int wp, rp;
public:
    ProbSolvLec()
    {
        _Solve();
    }
    ~ProbSolvLec(){}
private:
    void _Solve(){
        wp = rp = 0;
        scanf("%d", &N);
        int cmd = 0;
        int num = 0;
        FOR(i, N){
            scanf("%d", &cmd);
            if (cmd == 1){
                scanf("%d", &num);
                _EnQ(num);
            }
            else if (cmd == 0){
                if (_Empty() == true){
                    cout << "E"<<endl;
                }
                else {
                    cout << _Front() <<endl; _DeQ();
                }
            }
            else {
                cout << _Length() <<endl;
            }
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
    void _DeQ(){ rp++; }
    int _Length(){
        W_IFNOT(wp >= rp);
        return wp-rp;
    }
    bool _Empty(){ return wp == rp; }
};

class ProbSolv
{
    int Q[MAX];
    int rp = 0;
    int wp = 0;
public:
    ProbSolv()
    {
        _Solve();
    }
    ~ProbSolv(){}
private:
    void _Solve(){

        int numLines = 0;
        scanf("%d", &numLines);

        int cmd = -1;
        int num = -1;
        FOR(i, numLines){
            scanf("%d", &cmd);
            if (cmd == 1){
                scanf("%d", &num);
                EnQ(num);
            }
            else if(cmd == 0){
                DeQ();
            }
            else{
                cout << wp - rp <<endl;
            }
        }

    }

    int EnQ(int d){
        if (wp >= MAX) return 0;
        Q[wp++] = d;
        return 1;
    }

    int DeQ(){
        if (wp == rp){
            cout << "E"<<endl;
            return 0;
        }
        int p = Q[rp++];
        cout << p <<endl;
        return p;
    }

};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    // ProbSolv ps;
    ProbSolvLec ps;
    return 0;
}
