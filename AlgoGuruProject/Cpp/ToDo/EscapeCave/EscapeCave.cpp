#if 0
#define TEST
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
	int m_H, m_W, m_T;//지도 세로크기, 지도 가로크기, 제한 시간
	vvi m_map;
	int m_minT;
	int m_minT2Ex;
	int m_minTEx2Goal;
	queue<i_ii> m_qi_ii;
	ii m_iiEx;
public:
    ProbSolv()
    {
		InputData();
        
#ifdef TEST_OK
        cout <<endl;
        FOR(i, m_H){
            FOR(j, m_W){
                cout << m_map[i][j] << " ";
            }
            cout <<endl;
        }
#endif
        _Solve();
    }
    ~ProbSolv(){}
	int Get(const ii &pos){
		return m_map[pos.first][pos.second];
	}
	void Set(const ii &pos, const int val){
		m_map[pos.first][pos.second] = val;
	}
	bool Check(const ii &pos, const ii& finish){
		return ((pos.first == finish.first) && (pos.second == finish.second));
	}
	
	void BFS(const ii &start, const ii &finish, const bool onEx){
		m_qi_ii.push(i_ii(0, start));
		
		int timeLimit = 0;
		while (!m_qi_ii.empty()){
			i_ii t_pos = m_qi_ii.front(); m_qi_ii.pop();
			int time = t_pos.first;
			ii pos = t_pos.second;
			Set(pos, -1);
			
#ifdef TEST
			cout << t_pos.first << ": " << t_pos.second.first << "," <<t_pos.second.second <<endl;
#endif
			if (time > m_T){
				break;
			}
			else {
				if ((finish.first == m_iiEx.first) && (finish.second == m_iiEx.second)){
					if (time > m_minT2Ex){
						break;
					}
				}
				else if ((start.first == m_iiEx.first) && (start.second == m_iiEx.second)){
					if (time > m_minTEx2Goal){
						break;
					}
				}
			}
			
			if ((pos.first == finish.first) && (pos.second == finish.second)){
				if ((pos.first == (m_W-1)) && (pos.second == (m_H-1))){
					if ((start.first == m_iiEx.first) && (start.second == m_iiEx.second)){
						//m_minTEx2Goal;
						if (time < m_minTEx2Goal) {
							m_minTEx2Goal = time;
						}
#ifdef TEST
						cout << "Fin arrived" << time << ": " << pos.first << "," <<pos.second <<endl;
#endif
						break;	
					}
					else {
						// m_minT;
						if (time < m_minT) {
							m_minT = time;
						}
#ifdef TEST
						cout << "Fin arrived" << time << ": " << pos.first << "," <<pos.second <<endl;
#endif
						break;
						
					}
				}
				if ((pos.first == m_iiEx.first) && (pos.second == m_iiEx.second)){
					if (time < m_minT2Ex) {
						m_minT2Ex = time;
					}
#ifdef TEST
					cout << "Ex arrived" << time << ": " << pos.first << "," <<pos.second <<endl;
#endif
					break;
				}		
			}
			//*/
			FOR(dir, eDIR_LEN){
				ii npos = ii(pos.first + DIR[dir][0], pos.second + DIR[dir][1]);
				if(OOR(npos.first, 0, m_W-1)) continue;
				if(OOR(npos.second, 0, m_H-1)) continue;
				if(Get(npos) == -1) continue;
#ifdef TEST_OK
				if (Check(npos, m_iiEx)) 
					cout << "Error!!! " << time << ": " << pos.first << "," <<pos.second <<endl;
#endif
				if (onEx == false){
					if (Get(npos) == 1) continue;
				}

				Set(npos, -1);
				
				m_qi_ii.push(i_ii(time+1, npos));
			}
			//*/
			// if (++timeLimit >= 10) break;
			
		}
	}

private:
    void _Solve(){
		m_minT = m_T;
		m_minT2Ex = m_T;
		m_minTEx2Goal = m_T;
		ii start = ii(0,0);
		ii finish = ii(m_W-1,m_H-1);
		int answer = -1;
		
#ifdef TEST
		Timer.On("BFS(start, finish)");
#endif 
		BFS(start, finish, false);
#ifdef TEST
		Timer.Off();
        cout << "" << m_minT<<endl;
		Timer.On("BFS(start, excavator)");
#endif 
		BFS(start, m_iiEx, false);
#ifdef TEST
		Timer.Off();
		Timer.On("BFS(excavator, finish)");
#endif 
		BFS(m_iiEx, finish, true);
#ifdef TEST
		Timer.Off();
#endif 
		if ((m_minT2Ex + m_minTEx2Goal) < m_minT){
			m_minT = m_minT2Ex + m_minTEx2Goal;
		}
		if (m_minT <= m_T){
			answer = m_minT;
		}
		cout << answer;
    } // _Solve()

	void InputData(){
		cin >> m_H >> m_W >> m_T;
        FOR(i, m_H){
            vi rowG;
            FOR(j, m_W){
                int val;
                cin >> val;
				if (val == 2){
					m_iiEx = ii(i, j);
				}
                rowG.push_back(val);
            }
            m_map.push_back(rowG);
        }
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
