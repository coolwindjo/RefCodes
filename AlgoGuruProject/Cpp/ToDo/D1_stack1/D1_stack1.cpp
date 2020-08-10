// #include "../../ProbSolvStart.h"
#include <bits/stdc++.h>
using namespace std;

#define FOR_INC(i, from, to) for(int (i)=(from); (i)<(to); ++(i))
#define FOR_DEC(i, from, to) for(int (i)=(to)-1; (i)>=(from); --(i))
#define FOR(i, to) FOR_INC((i), 0, (to))
#define OOR(x, min, max) (((x) < (min) || (x) > (max)))

// const int MAX = 10000 + 10;
constexpr int MAX = (int)1e4;

class ProbSolvLec
{
public:
    ProbSolvLec()
    {
        _Solve();
    }
    ~ProbSolvLec();
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
};

class ProbSolv
{
    int N;
    int stack[MAX];
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
        stack[--sp] = d;
        return sp;
    }

    int Pop(){
        if (sp == MAX){
            cout << "E"<<endl;
            return -1;
        }
        int p = stack[sp++];
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
