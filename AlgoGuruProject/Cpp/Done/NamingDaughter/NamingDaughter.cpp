#include "../../ProbSolvStart.h"
constexpr int MAX_N = 2000 + 1;
constexpr int MAX_M = 2000 + 1;
enum Dir_e {
	eD = 0,
	eR,
	eDIR_LEN
};
constexpr int DIR[eDIR_LEN][2] = { { 1,0 },{ 0,1 } };

#if 1
#define USE_SORT_UNIQUE
#endif
class ProbSolv
{
	vvc m_map;
	vii m_viiPos;
	queue<ii> m_posQ;
	int m_rows;
	int m_cols;
	string m_ans;

#ifndef USE_SORT_UNIQUE
	vvstr m_vvstrVisit;
#endif // ~USE_SORT_UNIQUE

public:
	explicit ProbSolv() {
		_Solve();
	}
	~ProbSolv() {}

private:
	void _Solve() {
		int N = 0;
		int M = 0;
		cin >> N >> M;
		FOR(row, N) {
			vc vcRow;
			FOR(col, M) {
				char c;
				cin >> c;
				vcRow.push_back(c);
			}
			m_map.push_back(const_cast<const vc&>(vcRow));
		}
		m_rows = (int)m_map.size();
		m_cols = (int)m_map.front().size();

		string strName;
#if 0
		m_ans = "{";
		_DFSWithBackTracking(ii(0, 0), strName);
#else
		_BFSWithUniqueAndSmallest(ii(0, 0));
#endif // 0
		cout << m_ans << endl;
	}

	void _BFSWithUniqueAndSmallest(const ii &start) {

#ifndef USE_SORT_UNIQUE
		FOR(row, m_rows) {
			vstr vstrRow;
			FOR(col, m_cols) {
				vstrRow.push_back("{");
			}
			m_vvstrVisit.push_back(const_cast<const vstr&>(vstrRow));
		}
#endif // ~USE_SORT_UNIQUE

		m_ans = m_map[start.first][start.second];
		m_posQ.push(start);
		while (true) {
			m_viiPos.clear();
			while (!m_posQ.empty()) {
				const ii pos = m_posQ.front(); m_posQ.pop();
				FOR(dir, eDIR_LEN) {
					const ii nextPos = ii(pos.first + DIR[dir][0], pos.second + DIR[dir][1]);
					if (OOR(nextPos.first, 0, (int)(m_rows - 1))) continue;
					if (OOR(nextPos.second, 0, (int)(m_cols - 1))) continue;

#ifdef USE_SORT_UNIQUE
					m_viiPos.push_back(nextPos);
#else
 					// it works sometimes
					const string candName = m_ans + m_map[nextPos.first][nextPos.second];
					if (candName.compare(m_vvstrVisit[nextPos.first][nextPos.second]) < 0) {
						m_vvstrVisit[nextPos.first][nextPos.second] = candName;
						m_viiPos.push_back(nextPos);
					}
#endif // USE_SORT_UNIQUE
				}
			}

#ifdef USE_SORT_UNIQUE
			// Remove duplicates
			sort(m_viiPos.begin(), m_viiPos.end());
			m_viiPos.erase(unique(m_viiPos.begin(), m_viiPos.end()), m_viiPos.end());
#endif // USE_SORT_UNIQUE

			const int numCands = m_viiPos.size();
			if (numCands == 0) return;

			const ii firstInQ = m_viiPos[0];
			char earlistC = m_map[firstInQ.first][firstInQ.second];
			int earlistIdx = 0;
			FOR_INC(i, 1, numCands) {
				const ii pos = m_viiPos[i];
				const char ch = m_map[pos.first][pos.second];
				if (ch < earlistC) {
					earlistC = ch;
					earlistIdx = i;
				}
			}
			m_ans.push_back(earlistC);
			if ((m_viiPos.front().first == (m_rows - 1)) && (m_viiPos.front().second == (m_cols - 1))) {
				return;
			}

			const ii pos = m_viiPos[earlistIdx];
			if (m_map[pos.first][pos.second] == earlistC) {
				m_posQ.push(pos);
			}
		}
	}

	void _DFSWithBackTracking(const ii &pos, string &strNameOut) {
		strNameOut.push_back(m_map[pos.first][pos.second]);
		if ((pos.first == (int)(m_rows - 1)) && (pos.second == (int)(m_cols - 1))) {
			if (strNameOut.compare(m_ans) < 0) {
				m_ans = strNameOut;
			}
			return;
		}

		FOR(dir, eDIR_LEN) {
			const ii nextPos(pos.first + DIR[dir][0], pos.second + DIR[dir][1]);
			if (OOR(nextPos.first, 0, (int)(m_rows - 1))) continue;
			if (OOR(nextPos.second, 0, (int)(m_cols - 1))) continue;
			_DFSWithBackTracking(nextPos, strNameOut);
			strNameOut.pop_back();
		}
	}
};

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);

	int numTCs = 0;
	cin >> numTCs;
	FOR(tc, numTCs) {
		cout << "#" << tc + 1 << " ";
		ProbSolv ps;
	}

	return 0;
}