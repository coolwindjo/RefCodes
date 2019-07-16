#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

static const int WarnIfNot(const int condFlag, const char* condition) {
	if (condFlag == 0)
	{
		cout << "Warning: [" << condition << "] is violated!\n";
	}
	return condFlag;
}
#define W_IFNOT(cond) WarnIfNot((cond), (#cond))
#define P_IFNOT(cond, var) if(!W_IFNOT(cond)) cout << "= " << (var) <<endl;
#define FOR_INC(i, from, to) for(int (i)=(from); (i)<(to); (i)++)
#define FOR_DEC(i, from, to) for(int (i)=(to)-1; (i)>=(from); (i)--)
#define FOR(i, to) FOR_INC((i), 0, (to))
#define OOR(val, min, max) ((val)<(min))||((val)>(max))

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<size_t> vu;
typedef vector<vu> vvu;
typedef vector<char> vc;
typedef vector<vc> vvc;
typedef vector<string> vstr;
typedef vector<vstr> vvstr;

constexpr size_t INF = (size_t)1e9;
constexpr int MAX_N = 2000 + 1;
constexpr int MAX_M = 2000 + 1;
enum Dir_e {
	eD = 0,
	eR,
	//eU,
	//eL,
	eDIR_LEN
};
constexpr int DIR[eDIR_LEN][2] = { { 1,0 },{ 0,1 } };
//, {-1,0}, {0,-1} };

class CProbSolv
{
	vvc m_map;
	vii m_viiPos;
	queue<ii> m_posQ;
	size_t m_rows;
	size_t m_cols;
	string m_ans;

public:
	explicit CProbSolv(const int N, const int M) {
		FOR(row, N) {
			vc vcRow;
			FOR(col, M) {
				char c;
				cin >> c;
				vcRow.push_back(c);
			}
			m_map.push_back(const_cast<const vc&>(vcRow));
		}
		m_rows = m_map.size();
		m_cols = m_map.front().size();
		_Solve();
	}
	~CProbSolv() {}

private:
	void _Solve() {
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
		m_ans = m_map[start.first][start.second];
		m_posQ.push(start);
		while (true) {
			while (!m_posQ.empty()) {
				const ii pos = m_posQ.front(); m_posQ.pop();
				FOR(dir, eDIR_LEN) {
					const ii nextPos = ii(pos.first + DIR[dir][0], pos.second + DIR[dir][1]);
					if (OOR(nextPos.first, 0, (int)(m_rows - 1))) continue;
					if (OOR(nextPos.second, 0, (int)(m_cols - 1))) continue;
#if 0 // it works sometimes
					const string candName = m_ans + m_map[nextPos.first][nextPos.second];
					if (candName.compare(m_visit[nextPos.first][nextPos.second]) < 0) {
						m_visit[nextPos.first][nextPos.second] = candName;
						m_viiPos.push_back(nextPos);
					}
#else
					m_viiPos.push_back(nextPos);
#endif // 0
				}
			}
			m_viiPos.erase(unique(m_viiPos.begin(), m_viiPos.end()), m_viiPos.end());
			const int numCands = m_viiPos.size();
			if (numCands == 0) return;

			char earlistC = m_map[m_viiPos[0].first][m_viiPos[0].second];
			FOR_INC(i, 1, numCands) {
				const char ch = m_map[m_viiPos[i].first][m_viiPos[i].second];
				if (ch < earlistC) {
					earlistC = ch;
				}
			}
			m_ans.push_back(earlistC);
			if ((m_viiPos.front().first == (int)(m_rows - 1)) && (m_viiPos.front().second == (int)(m_cols - 1))) {
				return;
			}

			FOR(i, numCands) {
				if (m_map[m_viiPos[i].first][m_viiPos[i].second] == earlistC) {
					m_posQ.push(m_viiPos[i]);
				}
			}
			m_viiPos.clear();
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
		int N = 0;
		int M = 0;
		cin >> N >> M;
		cout << "#" << tc + 1 << " ";
		CProbSolv ps(N, M);
	}

	return 0;
}