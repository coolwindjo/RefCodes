#if 1
#define TEST
#endif // 1

#include "../../ProbSolvStart.h"

class ProbSolv
{
    int brown;
    int yellow;
public:
    ProbSolv()
    {
        cin >> brown >> yellow;

        _Solve();
    }
    ~ProbSolv(){}
private:
    void _Solve(){
        int b = brown;
        int y = yellow;
        int hori = 0;
        int verti = 0;
        // b + y = h*v

        // b = 2*h + 2*(v-2) = 2*(h+v-2)
        // h + v = b/2 + 2

        // h*v + (h+v) = (h+1)*(v+1) - 1
        // (b+y) + (b/2 + 2) + 1 = (h+1)*(v+1) // !
        int hvSum = b/2 + 2;
        int fixedNum = (b+y) + (b/2 + 2) + 1;
        FOR(v, hvSum){
            int h = hvSum - v;
            if (fixedNum == (h+1)*(v+1)){
                hori = max(h, v);
                verti = min(h, v);
                break;
            }
        }

        cout << "[" << hori << ", " << verti << "]";

        // not applicable solution
        // b + y = (b/2 - v + 2) * v
        // b + y = -v*v + (2+(b/2))*v
        // v*v + (2+(b/2))*v + (b+y) = 0
        // v = (-(2+(b/2)) +- ((2+(b/2))^2-4(b+y))^(1/2))/2
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
