#include "../../ProbSolvStart.h"

typedef enum {
	eR=0, eD, eL, eU, eDIR_LEN
} DIR_e;
constexpr int DIR[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
constexpr int MAX_HEIGHT = 20;

//#define TEST
class ProbSolv
{
	size_t m_mapSizeN;
	size_t m_maxDigK;
	vvii m_map;
	int m_peak;
	int m_deepest;
	vii m_viiStartingPos;
	vii m_viiPos;
	int m_maxDist;

public:
	explicit ProbSolv(const size_t N, const size_t K) {
		m_mapSizeN = N;
		m_maxDigK = K;
		m_peak = 0;
		m_deepest = MAX_HEIGHT;
		m_maxDist = 0;
		FOR(row, (int)m_mapSizeN) {
			vii viiRow;
			FOR(col, (int)m_mapSizeN) {
				int val = 0;
				cin >> val;
				viiRow.push_back(ii(0, val)); // ii(bVisited, Height)
				if (val >= m_peak)
				{
					m_peak = val;
					m_viiPos.push_back(ii(row, col));
				}
				if (val < m_deepest)
				{
					m_deepest = val;
				}
			}
			m_map.push_back(viiRow);
		}
		_Solve();
	}
	virtual ~ProbSolv() {}

	void DFS(const ii& pos, const int dist, const bool bDigged) {
		// Visit!
		m_map[pos.first][pos.second].first = 1;
		const int height = m_map[pos.first][pos.second].second;
#ifdef TEST
		cout << endl;
		FOR(i, dist) {
			cout << " ";
		}
		cout << pos.first << "," << pos.second << ":" << height;
#endif // TEST


		if (dist > m_maxDist)
		{
			m_maxDist = dist;
#ifdef TEST
			cout << " ===> " << m_maxDist;
#endif // TEST
		}

		// Check if it's a deepest point
		if (height == m_deepest)
		{
			if (bDigged == 1) {
				m_map[pos.first][pos.second].first = 0; // backtracking!
				return;
			}
		}

		if ((size_t)dist == m_mapSizeN * m_mapSizeN) {
			m_map[pos.first][pos.second].first = 0; // backtracking!
			return;
		}

		// look up 4 dirs
		FOR(dir, eDIR_LEN) {
			const ii nextPos(pos.first + DIR[dir][0], pos.second + DIR[dir][1]);
			if (OOR(nextPos.first, 0, (int)m_mapSizeN - 1)) continue;
			if (OOR(nextPos.second, 0, (int)m_mapSizeN - 1)) continue;
			if (m_map[nextPos.first][nextPos.second].first) continue;
			const int nextH = m_map[nextPos.first][nextPos.second].second;
			if (bDigged == 0) {
				// with optional digging
				if ((height - (nextH - (int)m_maxDigK)) <= 0) continue;
				int digging = height - nextH;
				if (digging <= 0) {
					P_IFNOT((1 - digging) <= (int)m_maxDigK, height);
					P_IFNOT((1 - digging) <= (int)m_maxDigK, nextH);
					P_IFNOT((1 - digging) <= (int)m_maxDigK, digging);
					m_map[nextPos.first][nextPos.second].second = nextH + (digging-1);
					DFS(nextPos, dist + 1, 1);
					// backtracking!
					m_map[nextPos.first][nextPos.second].second = nextH;
					continue;
				}
			}
			else {
				// without digging
				if (height - nextH <= 0) continue;
			}
			DFS(nextPos, dist + 1, bDigged);
		}

		m_map[pos.first][pos.second].first = 0; // backtracking!
	}
	
private:
	void _Solve(){
		// Set starting peaks
		P_IFNOT(m_viiPos.size() >= 1, m_viiPos.size());
		while (!m_viiPos.empty()) {
			const ii pos = m_viiPos.back(); m_viiPos.pop_back();
			if (m_peak == m_map[pos.first][pos.second].second)
			{
				m_viiStartingPos.push_back(pos);
			}
		}

		// DFS with backtracking
		P_IFNOT(m_viiStartingPos.size() >= 1, m_viiStartingPos.size());
		while (!m_viiStartingPos.empty()) {
			const ii pos = m_viiStartingPos.back(); m_viiStartingPos.pop_back();
			bool bDigged = 0;
#ifdef TEST
			cout << "\nStart from:" << pos.first << pos.second;
#endif // TEST
			DFS(pos, 1, bDigged);
#ifdef TEST
			cout << "\n++++++++++++" <<endl;
#endif // TEST
		}
		cout << m_maxDist << endl;
	}

};

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int numTCs = 0;
	cin >> numTCs;
	FOR(tc, numTCs) {
		size_t N = 0;
		size_t K = 0;
		cin >> N >> K;
		cout << "#" << tc + 1 << " ";
		ProbSolv ps(N,K);
	}

	return 0;
}
