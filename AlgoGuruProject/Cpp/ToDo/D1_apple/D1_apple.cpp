#include "../../ProbSolvStart.h"

typedef enum {
	eR=0, eD, eL, eU, eDIR_LEN
} Dir_e;
constexpr int DIR[eDIR_LEN][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };


class ProbSolv
{
public:
    ProbSolv()
    {
        _Solve();
    }
    ~ProbSolv(){}
private:
    void _Solve(){

#if 0
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

#if 0
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
#endif
        
    }

    // vector<int> cellCompete(int* states, int days){
    //     const int resIdx = days%2;
    //     return m_vviDualStates[resIdx];
    // }

};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int numTCs = 0;
    cin >> numTCs;
    FOR(tc, numTCs){
        cout << "#" << tc+1 <<" ";
        ProbSolv ps;
        cout << endl;
    }
    return 0;
}
