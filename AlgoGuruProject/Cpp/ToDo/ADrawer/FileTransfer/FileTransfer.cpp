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
        int ans = minimumHours(rows, columns, grid);
        cout << ans;
        
    }

	queue<ii> m_posQ;
    vii m_viiPos;
    vector<vvi> m_map;

int minimumHours(int rows, int columns, vector<vector<int> > grid)
{
    // WRITE YOUR CODE HERE
    m_map.push_back(grid);
    vii viiStarts;
    int i = 0;
    FOR(r, m_map[i].size()){
        FOR(c, m_map[i].front().size()){
            const int val = m_map[i][r][c];
            if (val == 1){
                viiStarts.push_back(ii(r,c));
            }
        }
    }

    for(ii start : viiStarts){
        int cell = grid[start.first][start.second];
        m_posQ.push(start);
        while (true) {
                m_viiPos.clear();
                while (!m_posQ.empty()) {
                    const ii pos = m_posQ.front(); m_posQ.pop();
                    FOR(dir, eDIR_LEN) {
                        const ii nextPos = ii(pos.first + DIR[dir][0], pos.second + DIR[dir][1]);
                        if (OOR(nextPos.first, 0, (int)(rows - 1))) continue;
                        if (OOR(nextPos.second, 0, (int)(columns - 1))) continue;

                        m_viiPos.push_back(nextPos);
                    }
                }

                // Remove duplicates
                sort(m_viiPos.begin(), m_viiPos.end());
                m_viiPos.erase(unique(m_viiPos.begin(), m_viiPos.end()), m_viiPos.end());

                const int numCands = m_viiPos.size();
                if (numCands == 0) return;

                const ii firstInQ = m_viiPos[0];
                char earlistC = grid[firstInQ.first][firstInQ.second];
                int earlistIdx = 0;
                FOR_INC(i, 1, numCands) {
                    const ii pos = m_viiPos[i];
                    const char ch = grid[pos.first][pos.second];
                    if (ch < earlistC) {
                        earlistC = ch;
                        earlistIdx = i;
                    }
                }
                m_ans.push_back(earlistC);
                if ((m_viiPos.front().first == (rows - 1)) && (m_viiPos.front().second == (m_cols - 1))) {
                    return;
                }

                const ii pos = m_viiPos[earlistIdx];
                if (grid[pos.first][pos.second] == earlistC) {
                    m_posQ.push(pos);
                }
            }
        }
    }

    return 0;
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
