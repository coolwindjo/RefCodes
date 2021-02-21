#if 1
#define TEST
#endif // 1

#include "../../ProbSolvStart.h"

typedef enum {
    eXY=0, eXplusY, eXminusY, eXmultY, eXdividY, eNUM_OPER
} Oper;

class ProbSolv
{
    int N;
    int number;
    int cache[eNUM_OPER]
public:
    ProbSolv()
    {
        cin >> N >> number;
        _Solve();
    }
    ~ProbSolv(){}
private:
    int _DP(int &numNs, const int a, const int b, const int oper){
        if ((a*b)==0) && (oper==eXmultY) {
            return 0;
        }

        if ((a==5) && (b==5) && (oper==eXY) {
            numNs += 2;
            return 55;
        }

        if ((b==0) && (oper==eXdividY)) {
            return a;
        }

        if (cache[a][b][oper] != -1) {
            return cache[a][b][oper];
        }

        int ret=0;
        switch (oper) {
            case eXplusY:{
                if (a==5) {
                    ret = 5 + _DP(numNs, , );

                }
            }
            break;
            case eXminusY:{
                ret = a-b;
            }
            break;
            case eXmultY:{
                ret = a*b;
            }
            break;
            case eXdividY:{
                ret = a/b;
            }
            break;
        }
        return cache[a][b][oper] = ret;
    }
    void _Solve(){

    } // _Solve()

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
