#if 1
#define TEST
#endif // 1

#include "../../ProbSolvStart.h"

typedef enum {
    eU=-1, eD=1,
    eDIR_LEN
} Dir_e;

class ProbSolv
{
    int numSteps;
    vi viPath;
public:
    ProbSolv()
    {
        cin >> numSteps;

        string strPath;
        while(strPath.length() == 0){
            std::getline(std::cin, strPath);    // get path removing \n
        }
        FOR(i, numSteps){
            if (strPath[i] == 'U') {
                viPath.push_back(eU);
            }
            else if (strPath[i] == 'D') {
                viPath.push_back(eD);
            }
            else{}
        }

        _Solve();
    }
    ~ProbSolv(){}
private:
    void _Solve(){
        int vCnt = 0;
        int level = 0;
        FOR (i, numSteps) {
            level += viPath[i];
            if (level == 0) {
                if (viPath[i] < 0) {
                    vCnt++;
                }
                else {}
            }
        }
        cout << vCnt;
    }

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
