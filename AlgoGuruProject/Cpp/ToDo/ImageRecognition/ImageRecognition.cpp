#if 0
#define TEST
#endif // 1
#if 1
#define SPLIT_DEBUG
#endif // 1

#include "../../ProbSolvStart.h"

#if 1   // 18dd
typedef enum {
	eR=0, eD,
    eL, eU,
    eDIR_LEN
} Dir_e;
constexpr int N_DIR[eDIR_LEN] = {eL, eU, eR, eD};
constexpr int DIR[eDIR_LEN][2] = {
    {0,1}, {1,0},
    {0,-1}, {-1,0}
};
#endif // 0

class ProbSolv
{
	int m_N;
    vvi m_grid;
	map<int, int> m_mapColorValidity;
public:
    ProbSolv()
    {
        int rows = 0;
        cin >> rows;
		m_N = rows;

        FOR(i, rows){
			string strVal;
			cin >> strVal;
            vi rowG;
            FOR(j, strVal.size()){
                rowG.push_back(strVal[j]-'0');
            }
            m_grid.push_back(rowG);
        }
#ifdef TEST_OK
        cout <<endl;
        FOR(i, rows){
            FOR(j, rows){
                cout << m_grid[i][j] << " ";
            }
            cout <<endl;
        }
#endif
        
        _Solve();
    }
    ~ProbSolv(){}

	ii GetNextPos(const ii &pos, const int dir){
		ii nPos = ii(pos.first+DIR[dir][0], pos.second+DIR[dir][1]);
		return nPos;
	}
	
	int GetColor(const ii &pos){
		if (OOR(pos.first, 0, m_N-1)) return -1;
		if (OOR(pos.second, 0, m_N-1)) return -1;
		return m_grid[pos.first][pos.second];
	}
	
	void DFS(const ii &pos, const int dir, const int clr, const int checkClr){
		ii nPos = GetNextPos(pos, dir);
		int nClr = GetColor(nPos);
		if (nClr == -1) return;
		if (nClr == clr) {
			DFS(nPos, dir, clr, checkClr);
		}
		else if (nClr == checkClr) {
			m_mapColorValidity[clr] = 0;
		}
	}
			
private:
	void _Solve(){
		unordered_set<int> hashClr;
		FOR(i, m_N){
			FOR(j, m_N){
				int clr = m_grid[i][j];
				if (clr == 0) continue;
				hashClr.insert(clr);
			}
		}
		for (auto clr : hashClr){
			m_mapColorValidity.insert(ii(clr, 1));
			int RDLU[eDIR_LEN] = {0,  	0,    m_N,  m_N };
								//maxC, maxR, minC, minR
			FOR(row, m_N){
				FOR(col, m_N){
					if (clr == m_grid[row][col]){
						if (RDLU[eR] < col) RDLU[eR] = col;
						if (RDLU[eD] < row) RDLU[eD] = row;
						if (RDLU[eL] > col) RDLU[eL] = col;
						if (RDLU[eU] > row) RDLU[eU] = row;
					}
				}
			}
			
#ifdef TEST
			FOR(rdlu, eDIR_LEN){
				cout << "Color:" << clr << "(" << rdlu << "):" << RDLU[rdlu] << endl;
			}
#endif
			FOR_INC(row, RDLU[eU], RDLU[eD]+1){
				FOR_INC(col, RDLU[eL], RDLU[eR]+1){
					int nClr = m_grid[row][col];
					if (nClr == clr) continue;
					m_mapColorValidity[nClr] = 0;
				}
			}
		}
		
#ifdef TEST
		for (auto clr_val : m_mapColorValidity){
			cout << "Color:" << clr_val.first << " Validity:" << clr_val.second << endl;
		}
#endif
		int clrCnt = 0;
		for (auto clr_val : m_mapColorValidity){
			if (clr_val.second == 1) clrCnt++;
		}
		cout << clrCnt;
	}
	
    void _Solve_UsingDFS(){
		unordered_map<int, vii> hashviiClr_PosList;
		typedef pair<int, vii> i_vii;
        FOR(i, m_N){
            FOR(j, m_N){
                int clr = m_grid[i][j];
				if (hashviiClr_PosList.find(clr) == hashviiClr_PosList.end()){
					vii viiPosList;
					hashviiClr_PosList.insert(i_vii(clr, viiPosList));
				}
				hashviiClr_PosList[clr].push_back(ii(i, j));
            }
        }
		for (i_vii i_viiClr_PosList: hashviiClr_PosList){
			int clr = i_viiClr_PosList.first;
			if (clr == 0) continue;
			m_mapColorValidity.insert(ii(clr, 1));
			vii viiPos = i_viiClr_PosList.second;
			for (ii pos : viiPos){
				FOR(dir, eDIR_LEN){
					ii nPos = GetNextPos(pos, dir);
					int nClr = GetColor(nPos);
					if (nClr == -1) continue;
					if (nClr == clr) continue;
					if (nClr == 0) continue;
					FOR(ndir, eDIR_LEN){
						if (ndir == dir) continue;
						DFS(pos, ndir, clr, nClr);
					}
				}
			}
        }

#ifdef TEST
		for (auto clr_val : m_mapColorValidity){
			cout << "Color:" << clr_val.first << " Validity:" << clr_val.second << endl;
		}
#endif
		int clrCnt = 0;
		for (auto clr_val : m_mapColorValidity){
			if (clr_val.second == 1) clrCnt++;
		}
		cout << clrCnt;

#ifdef TEST_OK
		for (i_vii i_viiPosList : hashviiClr_PosList){
			cout << "Color: " << i_viiPosList.first << endl;
            for (auto pos : i_viiPosList.second){
                cout << pos.first << " " << pos.second << "\n";
            }
        }
#endif
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
