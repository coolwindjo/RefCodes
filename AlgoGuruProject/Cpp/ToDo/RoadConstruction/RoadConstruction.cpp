#if 1
#define TEST
#endif // 1
#if 1
#define SPLIT_DEBUG
#endif // 1

#include "../../ProbSolvStart.h"

typedef enum {
	eR=0, eD,
    eL, eU,
    eDIR_LEN
} Dir_e;
constexpr int DIR[eDIR_LEN][2] = {
    {0,1}, {1,0},
    {0,-1}, {-1,0}
};

class ProbSolv
{
	int m_N;
	vvi m_grid[2];
	int m_minC;  // for DFS
	pqi_ii m_pqi_ii;
public:
    ProbSolv()
    {
        cin >> m_N;

        FOR(row, m_N){
            vi rowG;
			vi rowInf;
			string line;
			FOR(t, 10){
				std::getline(std::cin, line);
				if (line.length() >= 2){
					break;
				}
			}
            FOR(col, m_N){
                rowG.push_back(line[col]-'0');
				rowInf.push_back(INF);
            }
            m_grid[0].push_back(rowG);
            m_grid[1].push_back(rowInf);
        }
#ifdef TEST_OK
        cout <<endl;
        FOR(row, m_N){
            FOR(col, m_N){
                cout << m_grid[0][row][col] << " ";
            }
            cout <<endl;
        }
#endif
        
        _Solve();
    }
    ~ProbSolv(){}

	void DFS(const ii &pos, const int cost){ // O(4^(100*100))
		if (cost > m_minC) return;
		if ((pos.first == (m_N-1)) && (pos.second == (m_N-1))){
			if (cost < m_minC) {
				m_minC = cost;
			}
			return;
		}
		FOR(dir, eDIR_LEN){
			ii npos = ii(pos.first+DIR[dir][0], pos.second+DIR[dir][1]);
			if (OOR(npos.first, 0, m_N-1)) continue;
			if (OOR(npos.second, 0, m_N-1)) continue;
			DFS(npos, cost + m_grid[0][pos.first][pos.second]);
		}
	}

	int GetCost(const ii &pos){
		return m_grid[0][pos.first][pos.second];
	}
	int GetTotalCost(const ii &pos){
		return m_grid[1][pos.first][pos.second];
	}
	void SetTotalCost(const ii &pos, const int cost){
		m_grid[1][pos.first][pos.second] = cost;
	}
	
	void Dijkstra(const ii &start){
		m_pqi_ii.push(i_ii(0, start));
		
		while (!m_pqi_ii.empty()){
			i_ii cost_pos = m_pqi_ii.top(); m_pqi_ii.pop();
			ii pos = cost_pos.second;
			if ((pos.first == m_N-1) && (pos.second == m_N-1)) break;
			FOR(dir, eDIR_LEN){
				ii npos = ii(pos.first+DIR[dir][0], pos.second+DIR[dir][1]);
				if (OOR(npos.first, 0, m_N-1)) continue;
				if (OOR(npos.second, 0, m_N-1)) continue;
				int sum = GetTotalCost(pos) + GetCost(npos);
				if (sum < GetTotalCost(npos)){
#ifdef TEST_OK
					cout << GetTotalCost(npos) << "=>" << sum << "(" << npos.first << ", " << npos.second <<") \n";
#endif
					SetTotalCost(npos, sum);
					m_pqi_ii.push(i_ii(-sum, npos));
				}
#ifdef TEST_OK
				cout << "(" << npos.first << ", " << npos.second <<") \n";
#endif
#ifdef TEST_OK
				cout <<endl;
				FOR(row, m_N){
					FOR(col, m_N){
						cout << m_grid[1][row][col] << " ";
					}
					cout <<endl;
				}
#endif	
			}
				
		}
	}
	
private:
    void _Solve(){
		ii start = ii(0,0);
		SetTotalCost(start, 0);
#ifdef TEST
		Timer.On("DFS");
#endif
		DFS(ii(0,0), 0);
#ifdef TEST
		Timer.Off();
#endif
#ifdef TEST
		Timer.On("Dijkstra");
#endif
		Dijkstra(start);
#ifdef TEST
		Timer.Off();
#endif
#ifdef TEST_OK
        cout <<endl;
        FOR(row, m_N){
            FOR(col, m_N){
                cout << m_grid[1][row][col] << " ";
            }
            cout <<endl;
        }
#endif
        
		cout << m_grid[1][m_N-1][m_N-1];
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
