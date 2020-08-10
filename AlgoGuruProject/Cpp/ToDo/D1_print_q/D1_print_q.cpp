// #include "../../ProbSolvStart.h"
#include <bits/stdc++.h>
using namespace std;

#define FOR_INC(i, from, to) for(int (i)=(from); (i)<(to); ++(i))
#define FOR_DEC(i, from, to) for(int (i)=(to)-1; (i)>=(from); --(i))
#define FOR(i, to) FOR_INC((i), 0, (to))
#define OOR(x, min, max) (((x) < (min) || (x) > (max)))

// const int MAX = 10000 + 10;
constexpr int MAX = (int)1e4;

class ProbSolv
{
    int N;
    int que[MAX];
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
                Enqueue(num);
            }
            else if(cmd == 0){
                Dequeue();
            }
            else{
                cout << wp - rp <<endl;
            }
        }

    }

    int Enqueue(int d){
        if (wp >= MAX) return 0;
        que[wp++] = d;
        return 1;
    }
    int front(){
        return que[rp];
    }
    int back(){
        return que[wp-1];
    }
    int Dequeue(){
        if (wp == rp){
            cout << "E" <<endl;
            return 0;
        }
        int p = que[rp++];
        cout << p <<endl;
        return p;
    }
    int size(){
        return wp-rp;
    }
    int empty(){
        return wp==rp;
    }

};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    ProbSolv ps;
    return 0;
}
