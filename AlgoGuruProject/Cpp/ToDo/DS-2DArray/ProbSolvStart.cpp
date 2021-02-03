#if 1
#define TEST
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
#ifdef TEST
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
