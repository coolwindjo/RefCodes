#if 1
#define SPLIT_DEBUG
#endif // 1

#include "../../ProbSolvStart.h"

#if 0   // 12dd
typedef enum {
	eR=0, eD,
    eL, eU,
    eDIR_LEN
} Dir_e;
constexpr int DIR[eDIR_LEN][2] = {
    {0,1}, {1,0},
    {0,-1}, {-1,0}
};
#endif // 0

class ProbSolv
{
public:
    ProbSolv()
    {
#if 0   // 43dd
        int numLines = 0;
        cin >> numLines;

        vstr lines;
        FOR(i, numLines){
            string line;
            std::getline(std::cin, line);
            if(line.length() == 0){
                i--;
                continue;
            }
            lines.push_back(line);
        }
#endif

#if 0   // 27dd
        int rows = 0;
        int columns = 0;
        cin >> rows;
        cin >> columns;

        vvi grid;
        FOR(i, rows){
            vi rowG;
            FOR(j, columns){
                int val;
                cin >> val;
                rowG.push_back(val);
            }
            grid.push_back(rowG);
        }
#ifdef SPLIT_DEBUG
        cout <<endl;
        FOR(i, rows){
            FOR(j, columns){
                cout << grid[i][j] << " ";
            }
            cout <<endl;
        }
#endif
#endif
        
        _Solve();
    }
    ~ProbSolv(){}

private:
    void _Solve(){

    } // _Solve()

#if 0 // 48dd
    vstr _SplitString(string line, const string &delims) {
#ifdef SPLIT_DEBUG
        cout << "\n1) line: " << line <<endl;
#endif
        string::iterator newEnd = unique(line.begin(), line.end(), [] (const char &x, const char &y) {
            return x==y and x==' ';
        });
#ifdef SPLIT_DEBUG
        cout << "2) line: " << line <<endl;
#endif

        line.erase(newEnd, line.end());
#ifdef SPLIT_DEBUG
        cout << "3) line: " << line <<endl;
#endif

        while (line[line.length() - 1] == ' ') {
            line.pop_back();
        }
#ifdef SPLIT_DEBUG
        cout << "4) line: " << line <<endl;
#endif

        vstr vstrSplits;

        size_t prev = 0;
        size_t pos;
        while ((pos = line.find_first_of(delims, prev)) != string::npos) {
            if (pos > prev) {
                vstrSplits.push_back(line.substr(prev, pos-prev));
            }
#ifdef SPLIT_DEBUG
            for(string str : vstrSplits) {
                cout << str << " ";
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
#endif

};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#if 0   // 6dd
    int numTCs = 0;
    cin >> numTCs;
    FOR (tc, numTCs) {
        cout << "#" << tc+1 <<" ";
#endif
        ProbSolv ps;
#if 0   // 4dd
        cout << endl;
    }
#endif
    return 0;
}
