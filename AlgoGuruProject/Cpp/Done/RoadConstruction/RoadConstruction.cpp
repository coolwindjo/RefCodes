#include "../../ProbSolvStart.h"

typedef enum {
	eR = 0, eD, eL, eU, eDIR_LEN
} Dir_e;

constexpr int DIR[eDIR_LEN][2] = { {0,1},{1,0},{0,-1},{-1,0} };

#ifdef TEST
static size_t cnt = 0U;
#endif // TEST
class ProbSolve
{
	int m_mapSizeN;
	vvii m_map;
	priority_queue<i_ii> m_pqiiPos;
	int m_minCost;

public:
	explicit ProbSolve(const int N) {
		m_mapSizeN = N;
		m_minCost = INF;
		FOR(row, m_mapSizeN) {
			vii viiRow;
			int cnt = 0;
			while (cnt < m_mapSizeN) {
				const char cVal = cin.get();
				const int val = cVal - '0';
				if (val >= 0 && val <= 9) {
					viiRow.push_back(ii(INF, val));
					cnt++;
				}
			}
			m_map.push_back(viiRow);
		}
		_Solve();
	}
	virtual ~ProbSolve(){}

private:
	void _Solve() {
		_Dijkstra(ii(0,0), ii(m_mapSizeN-1, m_mapSizeN-1));
#ifdef TEST
		cout << "Visit count: " << cnt;
		_PrintMap();
#endif // TEST
		cout << m_minCost << endl;
	}

	void _Dijkstra(const ii start, const ii finish) {
		m_pqiiPos.push(i_ii(-m_map[start.first][start.second].second, start));
		while (!m_pqiiPos.empty()) {
			const i_ii cost_pos = m_pqiiPos.top(); m_pqiiPos.pop();
			const int cost = -cost_pos.first;
			const int row = cost_pos.second.first;
			const int col = cost_pos.second.second;

			// Check if it's deprecated cost
            P_IFNOT(cost >= 0, cost);
			if (cost > m_map[row][col].first) continue;

			FOR(dir, eDIR_LEN) {
				const int nextRow = row + DIR[dir][0];
				const int nextCol = col + DIR[dir][1];
				if (OOR(nextRow, 0, m_mapSizeN - 1)) continue;
				if (OOR(nextCol, 0, m_mapSizeN - 1)) continue;
				const int nextCost = cost + m_map[nextRow][nextCol].second;

				// Check if it's smaller cost
				if (nextCost >= m_map[nextRow][nextCol].first) continue;

				// Visit
				m_map[nextRow][nextCol].first = nextCost;
#if 1
				// Check if it reaches the finish point
				if ((nextRow == finish.first) && (nextCol == finish.second)) {
					m_minCost = nextCost;
					return;
				}
#endif // 1
#ifdef TEST
				cnt++;
#endif // TEST
				// Add next cell to start from
				m_pqiiPos.push(i_ii(-nextCost, ii(nextRow, nextCol)));
			}
		}

		m_minCost = m_map[finish.first][finish.second].first;
	}
	
	void _PrintMap() {
		FOR(row, m_mapSizeN) {
			cout << "\n";
			FOR(col, m_mapSizeN) {
				cout << m_map[row][col].first << " ";
			}
		}
		cout << "\n";
	}
};

int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int N = 0;
	cin >> N;
	ProbSolve ps(N);
	return 0;
}
