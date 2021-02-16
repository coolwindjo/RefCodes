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
        int h = 0;
        int v = 0;
        // b + y = h*v

        // b = 2*h + 2*(v-2) = 2*(h+v-2)
        // h + (v-2) = b/2
        // h + v = b/2 +2

        // h*v + (h+v) = (h+1)*(v+1) - 1
        // (b+y) + (b/2 + 2) + 1 = (h+1)*(v+1)

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
