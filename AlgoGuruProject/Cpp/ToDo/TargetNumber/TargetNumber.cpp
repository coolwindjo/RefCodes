#if 0
#define TEST
#endif // 1

#include "../../ProbSolvStart.h"

typedef enum {
	eP=0, eM,
    ePMLEN
} Dir_e;
constexpr int OPER[ePMLEN] = {+1, -1};

constexpr int MAX_N = 20+1;
constexpr int MAX_T = 1000+1;

class ProbSolv
{
public:
    int a[MAX_N];
    int n;
    int t;
    int numSols;
    ProbSolv()
    {
        string line;
        FOR(i, 10){
            std::getline(std::cin, line);
            if(line.length() >= 2){
                break;
            }
        }
        cin >> t;

        string delims{", []\r"};
        vstr vstrNums = _SplitString(line, delims);
        int numCnt = 0;
        for (string num : vstrNums) {
            a[numCnt++] = std::stoi(num);
        }
        n = numCnt;

        _Solve();
    }
    ~ProbSolv(){}

    void DFS(const int idx, const int sol) {
        if (idx == n) {
            if (sol == t) {
                numSols++;
            }
            return;
        }
        
        for (int pm = eP; pm < ePMLEN; ++pm){ 
            DFS(idx+1, sol+OPER[pm]*a[idx]);
        }
        
    }

private:
    void _Solve(){
        numSols = 0;
        DFS(0, 0);
        cout << numSols;
    } // _Solve()

    vstr _SplitString(string line, const string &delims) {
#ifdef TEST
        cout << "1) line: " << line <<endl;
#endif
        string::iterator newEnd = unique(line.begin(), line.end(), [] (const char &x, const char &y) {
            return x==y and x==' ';
        });
#ifdef TEST
        cout << "2) line: " << line <<endl;
#endif

        line.erase(newEnd, line.end());
#ifdef TEST
        cout << "3) line: " << line <<endl;
#endif

        while (line[line.length() - 1] == ' ') {
            line.pop_back();
        }
#ifdef TEST
        cout << "4) line: " << line <<endl;
#endif

        vstr vstrSplits;

        size_t prev = 0;
        size_t pos;
        while ((pos = line.find_first_of(delims, prev)) != string::npos) {
            if (pos > prev) {
                vstrSplits.push_back(line.substr(prev, pos-prev));
            }
#ifdef TEST
            for(string name : vstrSplits) {
                cout << name << " ";
            }
            cout <<endl;
#endif
            prev = pos + 1;
        }

        if (prev < line.length()) {
            vstrSplits.push_back(line.substr(prev, min(pos, line.length()) - prev + 1));
        }

        return vstrSplits;
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
