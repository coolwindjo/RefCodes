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
    int S[MAX+10];
    int sp;

public:
    ProbSolvLec()
    {
        _Solve();
    }
    ~ProbSolvLec(){}
private:
    void _Solve(){
        sp = 0;
        scanf("%d", &N);
        int cmd = 0;
        int num = 0;
        FOR(i, N){
            scanf("%d", &cmd);
            if (cmd == 1){
                scanf("%d", &num);
                _Push(num);
            }
            else if (cmd == 0) {
                if (_Empty() == true){
                    cout << "E" <<endl;
                }
                else {
                    cout << _Top() <<endl; _Pop();
                }
            }
            else {
                cout << _Length() <<endl;
            }
        }
    }
    void _Push(int d){
        if (W_IFNOT(sp < MAX)) {
            S[++sp] = d;
        }
    }
    int _Top() {
        W_IFNOT(sp > 0); return S[sp];
    }
    void _Pop(){sp--;}
    int _Length(){
        W_IFNOT(sp >= 0); return sp;
    }
    bool _Empty(){return sp == 0;}
};

class ProbSolv
{
    int S[MAX];
    int sp = MAX;
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
                Push(num);
            }
            else if(cmd == 0){
                Pop();
            }
            else{
                cout << MAX - sp <<endl;
            }
        }

    }

    int Push(int d){
        if (sp == 0) return -1;
        S[--sp] = d;
        return sp;
    }

    int Pop(){
        if (sp == MAX){
            cout << "E"<<endl;
            return -1;
        }
        int p = S[sp++];
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
