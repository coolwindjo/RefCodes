#include<iostream>
#include <cstring>
#include <queue>

//#define TEST

using namespace std;

inline int WarnIfNot(const int condFlag, const char* condition)
{
	if (condFlag == 0)
	{
		cout << "Warning: [" << condition << "] is violated!\n";
	}
	return condFlag;
}
#define W_IFNOT(condition) WarnIfNot((condition), (#condition))

static const size_t MAX_NUM_ROWS = 50U + 300U * 2U;
static const size_t MAX_NUM_COLS = 50U + 300U * 2U;
static const size_t MAP_BASE = MAX_NUM_ROWS >> 1;
static const int MAX_NUM_GENS = 300U + 1U;
static const int MAX_LIFE_TIME = 10U + 1U;
static const int DIR_NUM = 4;
static const int DIR[DIR_NUM][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };

typedef pair<int, int> ii;
typedef pair<ii, int> ii_i;
typedef ii CellLifeAndRemainingTime_t;	/**< LifeTime, RemainingTime */
typedef ii_i CellPos_t; /**< (RowIdx, ColIdx):44, RemainingTime */
CellLifeAndRemainingTime_t g_matMap[MAX_NUM_ROWS][MAX_NUM_COLS];
class CTest
{
	size_t m_N_inputNumRows;
	size_t m_M_inputNumCols;
	int m_K_inputNumGens;
	queue<CellPos_t> m_cellQ[MAX_LIFE_TIME][2];

public:
	CTest(const int N, const int M, const int K);
	~CTest();
	size_t GetMapPos(const int idx);
	//void UpdateCell(const int rowIdx, const int colIdx, const int value, const int timePast);
	CellLifeAndRemainingTime_t &FetchCell(const CellPos_t cellPos);
	void SetMapValue(const int rowIdx, const int colIdx, const int val, const int qIdx);
	int Simulate();
#ifdef TEST
	void PrintMap();
#endif // TEST


private:
	size_t m_beginRowIdx;
	size_t m_beginColIdx;
	size_t m_endRowIdx;
	size_t m_endColIdx;
};

CTest::CTest(const int N, const int M, const int K)
	: m_N_inputNumRows((size_t)N)
	, m_M_inputNumCols((size_t)M)
	, m_K_inputNumGens(K)
{
	(void)memset(&g_matMap[0][0], 0, sizeof(g_matMap));
	m_beginColIdx = MAX_NUM_COLS;
	m_beginRowIdx = MAX_NUM_ROWS;
	m_endColIdx = 0U;
	m_endRowIdx = 0U;
}

CTest::~CTest()
{
}
size_t CTest::GetMapPos(const int idx)
{
	return (size_t)(idx + MAP_BASE);
}

CellLifeAndRemainingTime_t & CTest::FetchCell(const CellPos_t cellPos)
{
	// TODO: insert return statement here
	return g_matMap[GetMapPos(cellPos.first.first)][GetMapPos(cellPos.first.second)];
}
void CTest::SetMapValue(const int rowIdx, const int colIdx, const int val, const int qIdx)
{
	const size_t mapRowIdx = GetMapPos(rowIdx);
	const size_t mapColIdx = GetMapPos(colIdx);

	if (mapRowIdx < m_beginRowIdx) { m_beginRowIdx = mapRowIdx; }
	if (mapColIdx < m_beginColIdx) { m_beginColIdx = mapColIdx; }
	if (mapRowIdx > m_endRowIdx) { m_endRowIdx = mapRowIdx; }
	if (mapColIdx > m_endColIdx) { m_endColIdx = mapColIdx; }

	CellPos_t cellPos;
	cellPos.first.first = rowIdx;
	cellPos.first.second = colIdx;
	const CellLifeAndRemainingTime_t &prevCell = FetchCell(cellPos);
	if (prevCell.first > val)
	{
		// Lower life time
		return;
	}
	else if (prevCell.first == val)
	{
		if (prevCell.second <= prevCell.first * 2)
		{
			// Older cell
			return;
		}
	}
	else
	{
		// New cell has higher life time
		if (prevCell.second < prevCell.first * 2)
		{
			// Older cell
			return;
		}
	}

	if (val > 0)
	{
		CellLifeAndRemainingTime_t &cellOut = FetchCell(cellPos);
		cellOut.first = val;
		cellOut.second = (val * 2);
		cellPos.second = cellOut.second;
		m_cellQ[val][qIdx].push(cellPos);
	}
}
int CTest::Simulate()
{
	for (int gen = 0; gen < m_K_inputNumGens; gen++)
	{
		const int i = gen % 2;
		const int ni = (gen + 1) % 2;
		for (int lifeTime = 1; lifeTime < MAX_LIFE_TIME; lifeTime++)
		{
			const size_t numCellByLifeTime = m_cellQ[lifeTime][i].size();
			for (size_t cellIdx = 0; (!m_cellQ[lifeTime][i].empty())&&(cellIdx < numCellByLifeTime); cellIdx++)
			{
				CellPos_t cellPos = m_cellQ[lifeTime][i].front(); m_cellQ[lifeTime][i].pop();

				CellLifeAndRemainingTime_t &cellOut = FetchCell(cellPos);

				if (cellOut.second != cellPos.second)
				{
					// Duplicate pos in Q
					continue;
				}

				const int remainingTime = cellOut.second--;
				if (remainingTime > lifeTime)
				{
					// Deactivated
					cellPos.second = cellOut.second;
					m_cellQ[lifeTime][ni].push(cellPos);
					continue;
				}

				if (remainingTime == lifeTime)
				{
					// Reproducing...
					for (int dirIdx = 0; dirIdx < DIR_NUM; dirIdx++)
					{
						const int newRowIdx = cellPos.first.first + DIR[dirIdx][0];
						const int newColIdx = cellPos.first.second+ DIR[dirIdx][1];
						SetMapValue(newRowIdx, newColIdx, lifeTime, ni);
					}
				}

				if (cellOut.second <= 0)
				{
					// Dead
					continue;
				}
				else
				{
					// Alive
					;
				}

				cellPos.second = cellOut.second;
				m_cellQ[lifeTime][ni].push(cellPos);
			}

		}
	}

	int validCellCnt = 0;
	const int finalQIdx = (m_K_inputNumGens) % 2;
	for (int j = 1; j < MAX_LIFE_TIME; j++)
	{
		const size_t numCellsByLifeTime = m_cellQ[j][finalQIdx].size();
		for (size_t i = 0; i < numCellsByLifeTime; i++)
		{
			if (!m_cellQ[j][finalQIdx].empty())
			{
				CellPos_t cellPos = m_cellQ[j][finalQIdx].front();
				CellLifeAndRemainingTime_t &cellOut = FetchCell(cellPos);
				if (cellOut.second > 0)
				{
					validCellCnt++;
					cellOut.second = -1;
				}
				m_cellQ[j][finalQIdx].pop();
			}
		}
	}
	return validCellCnt;
}
#ifdef TEST
void CTest::PrintMap()
{
	for (size_t i = m_beginRowIdx; i <= m_endRowIdx; i++)
	{
		for (size_t j = m_beginColIdx; j <= m_endColIdx; j++)
		{
			cout.width(3); cout << right << g_matMap[i][j].first << " ";
		}
		cout << "\n";
	}

	for (size_t i = m_beginRowIdx; i <= m_endRowIdx; i++)
	{
		for (size_t j = m_beginColIdx; j <= m_endColIdx; j++)
		{
			cout.width(3); cout << right << g_matMap[i][j].second << " ";
		}
		cout << "\n";
	}

	size_t maxLoops0 = 0;
	size_t maxLoops1 = 0;
	for (int i = 0; i < MAX_LIFE_TIME; i++)
	{
		if (m_cellQ[i][0].size() > maxLoops0)
		{
			if (m_cellQ[i][0].size() > maxLoops0)
			{
				maxLoops0 = m_cellQ[i][0].size();
			}
		}
		if (m_cellQ[i][1].size() > maxLoops1)
		{
			if (m_cellQ[i][1].size() > maxLoops1)
			{
				maxLoops1 = m_cellQ[i][1].size();
			}
		}
	}
	const size_t maxLoops = maxLoops0 > maxLoops1 ? maxLoops0 : maxLoops1;
	for (int j = 1; j < MAX_LIFE_TIME; j++)
	{
		cout << "Life" << j << ": ";
		for (int i = 0; i < maxLoops; i++)
		{
			for (int  k = 0; k < 2; k++)
			{
				if (!m_cellQ[j][k].empty())
				{
					cout << k << "(" << m_cellQ[j][k].front().first.first << m_cellQ[j][k].front().first.second << ")" << " ";
					m_cellQ[j][k].pop();
				}
			}

			cout << " ";
		}
		cout << "\n";
	}
}
#endif // TEST
int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int test_case;
	int T;
	cin >> T;
	/*
	여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{
		int N,M,K;
		cin >> N >> M >> K;
		W_IFNOT(N>0);
		W_IFNOT(M>0);
		W_IFNOT(K>0);
		CTest test(N, M, K);
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				int value;
				cin >> value;
				test.SetMapValue(i, j, value, 0);
			}
		}

		cout << "#" << test_case << " " << test.Simulate() << "\n";

#ifdef TEST
		test.PrintMap();
#endif // TEST


	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
