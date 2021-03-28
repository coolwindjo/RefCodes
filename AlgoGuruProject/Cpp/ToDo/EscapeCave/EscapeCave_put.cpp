#if 0
#define TEST
#endif // 1

#include <bits/stdc++.h>
using namespace std;

#if 1 // 61dd
class CoolTimer {
public:
    CoolTimer()
        : m_fn_name(nullptr)
        , m_fn_name_size(0)
    {
    }
    ~CoolTimer() {
        if (m_fn_name != nullptr) {
            delete[] m_fn_name;
            m_fn_name = nullptr;
        }
    }

    void On(const char* str) {
        // Get the name of the function.
        m_fn_name_size = strlen(str) + 1;
        if (m_fn_name == nullptr) {
            m_fn_name = new char[m_fn_name_size];
        }
        memcpy(m_fn_name, str, sizeof(char)*m_fn_name_size);

        // Start.
        _QueryPerformanceCounter(&m_begin);
    }

    void Off() {	
        // End.
        _QueryPerformanceCounter(&m_end);

        // Calculate the time.
        long seconds = m_end.tv_sec - m_begin.tv_sec;
        long nanoseconds = m_end.tv_nsec - m_begin.tv_nsec;
        double elapsed = seconds + nanoseconds*1e-9;

        // Print the message.
        ostringstream os;
        os << m_fn_name << "() takes [" << elapsed << "] seconds.\n"; 
        cout << os.str();
        if (m_fn_name != nullptr) {
            delete[] m_fn_name;
            m_fn_name = nullptr;
        }
    }
private:
    bool _QueryPerformanceCounter(timespec* performance_count) {
        /* Sanity check. */
        assert(performance_count != nullptr);
        /* Grab the current time. */
        clock_gettime(CLOCK_REALTIME, performance_count);
        return true;
    }

    timespec m_begin;
    timespec m_end;
    char* m_fn_name;
    size_t m_fn_name_size;
} Timer;
#endif

#pragma GCC optimize("O2") 
#define FOR_INC(i, from, to) for(int (i)=(from); (i)<(to); ++(i))
#define FOR_DEC(i, from, to) for(int (i)=(to)-1; (i)>=(from); --(i))
#define FOR(i, to) FOR_INC((i), 0, (to))
#define OOR(x, min, max) (((x) < (min) || (x) > (max)))

static const int WarnIfNot(const int condFlag, const char* condition){
 	if (condFlag == 0) {
        cout << "Warning: [" << condition << "] is violated!\n";
    }
    return condFlag;
}
#define W_IFNOT(cond) WarnIfNot((cond), (#cond))
#define P_IFNOT(cond, var) if (!W_IFNOT(cond)) cout << "= " << var <<endl;

typedef long long ll;
constexpr int INF = 987654321;

typedef vector<string> vstr;
typedef vector<vstr> vvstr;
typedef pair<int, string> i_str;
typedef vector<i_str> vistr;
typedef pair<string, int> str_i;
typedef vector<str_i> vstri;
typedef vector<char> vc;
typedef vector<vc> vvc;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef pair<int, ii> i_ii;
typedef queue<ii> qii;
typedef queue<int> qi;
typedef priority_queue<i_ii> pqi_ii;    // for Dijkstra

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
		Timer.On("BFS");
#endif 
		BFS(start, finish, false);
		BFS(start, m_iiEx, false);
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
    ProbSolv ps;
    return 0;
}
