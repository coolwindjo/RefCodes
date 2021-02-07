#if 1
#define TEST
#endif // 1

#include "../../ProbSolvStart.h"

class ProbSolv
{
    vstr vstrPartList;
    vstr vstrCompList;
public:
    ProbSolv()
    {
        string line;
        FOR(i, 10){
            std::getline(std::cin, line);
            if(line.length() != 0){
                break;
            }
        }
        vstrPartList = _SplitString(line);

        FOR(i, 10){
            std::getline(std::cin, line);
            if(line.length() != 0){
                break;
            }
        }
        vstrCompList = _SplitString(line);

#ifdef TEST
        
#endif

        _Solve();
    }
    ~ProbSolv(){}
private:
    void _Solve(){

    } // _Solve()

    vstr _SplitString(string line) {
        string::iterator newEnd = unique(line.begin(), line.end(), [] (const char &x, const char &y) {
            return x==y and x==' '
        });

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
