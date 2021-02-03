#if 0
#define TEST
#endif // 1

#include "../../ProbSolvStart.h"

class ProbSolv
{
    ll n;
    int numAsInSub;
    int sLen;
    vi viLocA;
public:
    ProbSolv()
    {
        string line;
        while (line.length() == 0) {
            std::getline(std::cin, line);
        }
        cin >> n;

        numAsInSub = 0;
        sLen = line.length();
        FOR(i, sLen){
            if (line[i] == 'a') {
                viLocA.push_back(i);
                numAsInSub++;
            }
        }

#ifdef TEST
        FOR(i, viLocA.size()){
            cout << viLocA[i] << " ";
        }
        cout <<endl;
#endif

        _Solve();
    }
    ~ProbSolv(){}
private:
    void _Solve(){
        ll quo = n/sLen;
        int rem = n%sLen;
        int aCnt = 0;
        FOR(i, viLocA.size()){
            if (viLocA[i] < rem) {
                aCnt++;
            }
            else {
                break;
            }
        }
        ll numAs = quo * numAsInSub + aCnt;
        cout << numAs;
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
