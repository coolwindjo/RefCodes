#include "../../ProbSolvStart.h"

typedef enum {
	eR=0, eD, eDIR_LEN
} Dir_e;

constexpr int DIR[eDIR_LEN][2] = { {0,1},{1,0} };

//#define TEST
class ProbSolve
{
	int m_mapSizeN;
	vvii m_map;
	vvi m_mapCanGo;
	int m_minZeros;

public:
	explicit ProbSolve(const int N) {
		m_minZeros = INF;
		m_mapSizeN = N;
		P_IFNOT(m_mapSizeN >= 2 , m_mapSizeN);
		P_IFNOT(m_mapSizeN <= 1000, m_mapSizeN);

		FOR(row, m_mapSizeN) {
			vii viiRow;
			vi viRow;
			FOR(col, m_mapSizeN) {
				int val = 0;
				cin >> val;
				P_IFNOT(val >= 0, val);
				int numTwos = INF;
				int numFives = INF;
				if (val > 0) {
					numTwos = CountFactor(2, val);
					numFives = CountFactor(5, val);
				}
				viiRow.push_back(ii(numTwos, numFives));
				viRow.push_back(val);
			}
			m_map.push_back(viiRow);
			m_mapCanGo.push_back(viRow);
		}

		_Solve();
	}
	virtual ~ProbSolve() {}

	int CountFactor(const int factor, const int val) {
		int cnt = 0;
		int quotient = val;
		while (quotient % factor == 0) {
			quotient /= factor;
			cnt++;
		}
		return cnt;
	}

	void UpdateFactorMap() {
		FOR_INC(row, 1, m_mapSizeN) {
			m_map[row][0].first += m_map[row - 1][0].first;
			if (m_map[row][0].first > INF) m_map[row][0].first = INF;
			m_map[row][0].second += m_map[row - 1][0].second;
			if (m_map[row][0].second > INF) m_map[row][0].second = INF;
		}
		FOR_INC(col, 1, m_mapSizeN) {
			m_map[0][col].first += m_map[0][col - 1].first;
			if (m_map[0][col].first > INF) m_map[0][col].first = INF;
			m_map[0][col].second += m_map[0][col - 1].second;
			if (m_map[0][col].second > INF) m_map[0][col].second = INF;
		}
		FOR_INC(row, 1, m_mapSizeN) {
			FOR_INC(col, 1, m_mapSizeN) {
				m_map[row][col].first += min(m_map[row - 1][col].first, m_map[row][col - 1].first);
				if (m_map[row][col].first > INF) m_map[row][col].first = INF;
				m_map[row][col].second += min(m_map[row - 1][col].second, m_map[row][col - 1].second);
				if (m_map[row][col].second > INF) m_map[row][col].second = INF;
			}
		}
		m_minZeros = min(m_map[m_mapSizeN - 1][m_mapSizeN - 1].first, m_map[m_mapSizeN - 1][m_mapSizeN - 1].second);
	}

	int min(const int a, const int b) {
		return (a < b ? a : b);
	}

	void DFS(const ii iiTwoFive, const int row, const int col) {
		if (m_mapCanGo[row][col] == 0) {
			W_IFNOT(m_mapCanGo[row][col] > 0);
			return;
		}

		const int accumTwo = iiTwoFive.first + m_map[row][col].first;
		const int accumFive = iiTwoFive.second + m_map[row][col].second;
#ifdef TEST
		cout << endl;
		FOR(i, row + col) cout << "	";
		cout << m_mapCanGo[row][col] << " is visited => (" << accumTwo << ", " << accumFive << ")";
#endif // TEST
		if ((row == (m_mapSizeN - 1))
			&& (col == (m_mapSizeN - 1))
			) {
			const int numZeros = accumTwo < accumFive ? accumTwo : accumFive;
			if (numZeros < m_minZeros) {
				m_minZeros = numZeros;
			}
#ifdef TEST
			cout << " result:" << "(" << accumTwo << ", " << accumFive << ")" << ":" << numZeros << "\n";
#endif // TEST
			return;
		}

		FOR(dir, eDIR_LEN) {
			const int nextRow = row + DIR[dir][0];
			const int nextCol = col + DIR[dir][1];
			if (OOR(nextRow, 0, m_mapSizeN - 1)) continue;
			if (OOR(nextCol, 0, m_mapSizeN - 1)) continue;
			if (m_mapCanGo[nextRow][nextCol] == 0) continue;
			DFS(ii(accumTwo, accumFive), nextRow, nextCol);
		}
	}

	typedef struct Node_t {
		Node_t(const int r, const int c, const int t, const int f)
			: row(r)
			, col(c)
			, numTwos(t)
			, numFives(f)
		{}
		int row;
		int col;
		int numTwos;
		int numFives;
	} Node_t;
	void DFSwithStack(const ii iiTwoFive, const int row, const int col) {
		stack<Node_t> S;
		S.push(Node_t(row, col, iiTwoFive.first, iiTwoFive.second));

		while (!S.empty()) {
			const Node_t node = S.top(); S.pop();
			if (m_mapCanGo[node.row][node.col] == 0) {
				W_IFNOT(m_mapCanGo[node.row][node.col] > 0);
				continue;
			}

			const int accumTwo = node.numTwos + m_map[node.row][node.col].first;
			const int accumFive = node.numFives + m_map[node.row][node.col].second;
#ifdef TEST
			cout << endl;
			FOR(i, node.row + node.col) cout << "	";
			cout << m_mapCanGo[node.row][node.col] << " is visited => (" << accumTwo << ", " << accumFive << ")";
#endif // TEST
			if ((node.row == (m_mapSizeN - 1))
				&& (node.col == (m_mapSizeN - 1))
				) {
				const int numZeros = accumTwo < accumFive ? accumTwo : accumFive;
				if (numZeros < m_minZeros) {
					m_minZeros = numZeros;
				}
#ifdef TEST
				cout << " result:" << "(" << accumTwo << ", " << accumFive << ")" << ":" << numZeros << "\n";
#endif // TEST
				continue;
			}

			FOR(dir, eDIR_LEN) {
				const int nextRow = node.row + DIR[dir][0];
				const int nextCol = node.col + DIR[dir][1];
				if (OOR(nextRow, 0, m_mapSizeN - 1)) continue;
				if (OOR(nextCol, 0, m_mapSizeN - 1)) continue;
				if (m_mapCanGo[nextRow][nextCol] == 0) continue;
				S.push(Node_t(nextRow, nextCol, accumTwo, accumFive));
			}
		}
	}

private:
	void _Solve() {
#if 1
		UpdateFactorMap();
#else
		//DFSwithStack(ii(0, 0), 0, 0);
		DFS(ii(0, 0), 0, 0);
#endif // 0
		cout << m_minZeros << endl;
	}

};

int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int numTCs = 0;
	cin >> numTCs;
	FOR(tc, numTCs) {
		int N = 0;
		cin >> N;
		cout << "#" << tc + 1 << " ";
		ProbSolve ps(N);
	}
	return 0;
}