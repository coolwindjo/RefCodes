#include "../../ProbSolvStart.h"

typedef enum {
	eR = 0, eD, eL, eU, eDIR_LEN
} Dir_e;

constexpr int DIR[eDIR_LEN][2] = { {0,1},{1,0},{0,-1},{-1,0} };
constexpr int MAX_MAP_SIZE = 50 + 1;
constexpr int MAX_LIFE_POWER = 10;
constexpr int MAX_TIME = 300 + 1;
constexpr int INIT_MAP_OFFSET = MAX_TIME / 2;
constexpr int MAX_NUM_ROWS = MAX_MAP_SIZE + MAX_TIME;
constexpr int MAX_NUM_COLS = MAX_MAP_SIZE + MAX_TIME;

#if 0
#define TEST
#define TEST_GEN 3
#endif // 1
int g_arMap[2][MAX_NUM_ROWS][MAX_NUM_COLS];	/**< [0]: Effective map, [1]: Temporary map to be determined by extention policy */
class ProbSolve
{
	int m_initRowsN;
	int m_initColsM;
	int m_timeLimitK;
	int m_mapMaxRows;
	int m_mapMaxCols;
	ii m_mapRowRange;
	ii m_mapColRange;

public:
	explicit ProbSolve(const int N, const int M, const int K) {
		(void)memset(&(g_arMap[0][0]), 0, sizeof(g_arMap));
		m_initRowsN = N;
		m_initColsM = M;
		m_timeLimitK = K;
		m_mapMaxRows = INIT_MAP_OFFSET + m_initRowsN + INIT_MAP_OFFSET;
		m_mapMaxCols = INIT_MAP_OFFSET + m_initColsM + INIT_MAP_OFFSET;
		m_mapRowRange.first = m_mapMaxRows;
		m_mapRowRange.second = 0;
		m_mapColRange.first = m_mapMaxCols;
		m_mapColRange.second = 0;
		FOR(row, m_initRowsN) {
			FOR(col, m_initColsM) {
				int val = 0;
				cin >> val;
				if (val > 0) {
					g_arMap[0][row + INIT_MAP_OFFSET][col + INIT_MAP_OFFSET] = val;
					g_arMap[1][row + INIT_MAP_OFFSET][col + INIT_MAP_OFFSET] = val;
					_UpdateRange(row + INIT_MAP_OFFSET, col + INIT_MAP_OFFSET);
				}
			}
		}

		_Solve();
	}
	virtual ~ProbSolve() {}

private:
	void _Solve() {

		_BFSwithGenerations();

#ifdef TEST
		_PrintMap();
#endif // TEST
		cout << _CountAlives() << "\n";
	}

	void _BFSwithGenerations() {
		queue<i_ii> arqLifePos[2];

		FOR_INC(row, m_mapRowRange.first, m_mapRowRange.second + 1) {
			FOR_INC(col, m_mapColRange.first, m_mapColRange.second + 1) {
				const int val = g_arMap[0][row][col];
				if (val > 0) {
					arqLifePos[0].push(i_ii(2 * val, (ii(row, col))));
				}
			}
		}

		// repeat the loop until time limit
		vector<i_ii> vPrevExtendedCells;
		FOR(gen, m_timeLimitK) {
			const int i = gen % 2;
			const int ni = (gen + 1) % 2;

#ifdef TEST
			cout << "\ngeneration #:" << gen + 1;
			cout << "\nbefore";
			_PrintMap();
#endif // TEST

			_UpdateMapAndQueue(vPrevExtendedCells, arqLifePos[i]);

			// visit all the stem cells in the current queue
			while (!arqLifePos[i].empty()) {
				const i_ii life_pos = arqLifePos[i].front(); arqLifePos[i].pop();
				const int row = life_pos.second.first;
				const int col = life_pos.second.second;

				// getting old
				const int life = life_pos.first - 1;
				if (life <= 0) {
					// dies
					g_arMap[0][row][col] = -1;
					continue;
				}

				// still alive: push into the next queue
				arqLifePos[ni].push(i_ii(life, ii(row, col)));
				const int val = g_arMap[0][row][col];
				if (life > val) continue;

				// now active!
				// for extention, the map is going to be updated in the next loop
				FOR(dir, eDIR_LEN) {
					const int nextRow = row + DIR[dir][0];
					const int nextCol = col + DIR[dir][1];
					P_IFNOT(!OOR(nextRow, 0, m_mapMaxRows - 1), nextRow);
					P_IFNOT(!OOR(nextCol, 0, m_mapMaxCols - 1), nextCol);
					if (g_arMap[0][nextRow][nextCol] != 0) continue;

					// previously empty cell
					if (val > g_arMap[1][nextRow][nextCol]) {
						g_arMap[1][nextRow][nextCol] = val;
						_UpdateRange(nextRow, nextCol);

						// extention candidates which will get old from the next after the next generation
						vPrevExtendedCells.push_back(i_ii(((2 * val) + 1), ii(nextRow, nextCol)));
					}
				}
			}	// while (!m_arqLifePos[i].empty())

#ifdef TEST
			cout << "\nafter";
			_PrintMap();
			if (gen == TEST_GEN) exit(0);
#endif // TEST

		} // FOR(gen, m_timeLimitK)
	}

	void _UpdateMapAndQueue(vector<i_ii> &vPrevExtendedCellsOut, queue<i_ii> &qLifePosOut)
	{
		while (!vPrevExtendedCellsOut.empty()) {
			const i_ii life_pos = vPrevExtendedCellsOut.back(); vPrevExtendedCellsOut.pop_back();
			const int row = life_pos.second.first;
			const int col = life_pos.second.second;
			const int val = g_arMap[1][row][col];
			if (life_pos.first == (2 * val) + 1) {
				// final extention value
				g_arMap[0][row][col] = val;

				// it start to get old from the next generation
				qLifePosOut.push(life_pos);
			}
		}
	}

	const int _CountAlives() {
		int cnt = 0;
		FOR_INC(row, m_mapRowRange.first, m_mapRowRange.second + 1) {
			FOR_INC(col, m_mapColRange.first, m_mapColRange.second + 1) {
				if (g_arMap[0][row][col] > 0) cnt++;
			}
		}
		return cnt;
	}

	void _UpdateRange(const int row, const int col) {
#ifdef TEST
		if (!W_IFNOT(row >= m_mapRowRange.first)) {
			m_mapRowRange.first = row;
			cout << "= " << row - INIT_MAP_OFFSET << endl;
		}
		if (!W_IFNOT(row <= m_mapRowRange.second)) {
			m_mapRowRange.second = row;
			cout << "= " << row - INIT_MAP_OFFSET << endl;
		}
		if (!W_IFNOT(col >= m_mapColRange.first)) {
			m_mapColRange.first = col;
			cout << "= " << col - INIT_MAP_OFFSET << endl;
		}
		if (!W_IFNOT(col <= m_mapColRange.second)) {
			m_mapColRange.second = col;
			cout << "= " << col - INIT_MAP_OFFSET << endl;
		}
#else
		if (row < m_mapRowRange.first) {
			m_mapRowRange.first = row;
		}
		if (row > m_mapRowRange.second) {
			m_mapRowRange.second = row;
		}
		if (col < m_mapColRange.first) {
			m_mapColRange.first = col;
		}
		if (col > m_mapColRange.second) {
			m_mapColRange.second = col;
		}
#endif // TEST
	}

	void _PrintMap(const int idx = -1) {
		int mapIdx = 0;
		if (idx != -1) mapIdx = idx;
		FOR_INC(row, m_mapRowRange.first, m_mapRowRange.second + 1) {
			cout << "\n";
			FOR_INC(col, m_mapColRange.first, m_mapColRange.second + 1) {
				cout << g_arMap[mapIdx][row][col] << " ";
			}
		}
		cout << "\n";
	}
};

int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int numTCs = 0;
	cin >> numTCs;
	FOR(tc, numTCs) {
		int N, M, K;
		cin >> N >> M >> K;
		cout << "#" << tc + 1 << " ";
		ProbSolve ps(N, M, K);
	}
	return 0;
}