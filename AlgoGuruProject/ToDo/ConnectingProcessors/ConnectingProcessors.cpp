#include "../../ProbSolvStart.h"

const int MAX_GRID = 12;
const int MAX_INT = (int)2e9;
typedef struct
{
	int row;
	int col;
} Node_t;
static const int NUM_DIRS = 4;
const int DIR[NUM_DIRS][2] = {
	{+1, 0},	// right
	{-1, 0},	// left
	{0, +1},	// down
	{0, -1}		// up
};
class CTest
{
	int m_gridSize;
	int m_matGrid[MAX_GRID][MAX_GRID];
	int m_numCores;
	int m_numConnected;
	int m_sumWireLen;
public:
	explicit CTest()
		: m_gridSize(0)
		, m_numCores(0)
		, m_numConnected(0)
		, m_sumWireLen(MAX_INT)
	{
		for (int i = 0; i < MAX_GRID; ++i)
		{
			m_arNode[i].row = 0;
			m_arNode[i].col = 0;
			for (int j = 0; j < MAX_GRID; ++j)
			{
				m_matGrid[i][j] = 0;
			}
		}
	}
	virtual ~CTest() {}
	void SetGridSize(const int gridSize)
	{
		// Guard clause
		if (!W_IFNOT(gridSize > 0)) return;
		m_gridSize = gridSize;
	}
	int GetGridSize() { return m_gridSize; }
	void SetGrid(const int(&matGrid)[MAX_GRID][MAX_GRID])
	{
		for (int i = 0; i < m_gridSize; ++i)
		{
			for (int j = 0; j < m_gridSize; ++j)
			{
				m_matGrid[i][j] = matGrid[i][j];
			}
		}
	}
	void PrintGrid()
	{
		for (int i = 0; i < m_gridSize; ++i)
		{
			for (int j = 0; j < m_gridSize; ++j)
			{
				cout << m_matGrid[i][j] << " ";
			}
			cout << endl;
		}
	}
	int ComputeSumWireLength()
	{
		if (!W_IFNOT(m_gridSize > 0))
			return -1;
		m_numCores = Init();
		int coreCnt = 0;
		int connectCnt = 0;
		int sumWireLen = 0;
		DFS(coreCnt, connectCnt, sumWireLen);
		return m_sumWireLen;
	}
private:
	int Init()
	{
		int coreCnt = 0;
		for (int i = 0; i < m_gridSize; ++i)
		{
			for (int j = 0; j < m_gridSize; ++j)
			{
				if (m_matGrid[i][j] == 1)
				{
					Node_t node;
					node.row = i;
					node.col = j;
					m_arNode[coreCnt++] = node;
				}
			}
		}
		return coreCnt;
	}
	void DFS(const int coreCnt, const int connectCnt, const int sumWireLen)
	{
		if (coreCnt == m_numCores)
		{
			if (connectCnt > m_numConnected)
			{
				m_numConnected = connectCnt;
				m_sumWireLen = sumWireLen;
			}
			else if (connectCnt == m_numConnected)
			{
				if (sumWireLen < m_sumWireLen)
				{
					m_sumWireLen = sumWireLen;
				}
			}
			return;
		}
		if (CheckNeighbors(m_arNode[coreCnt]) == 1)
		{
			DFS(coreCnt + 1, connectCnt + 1, sumWireLen);
			return;
		}
		int isConnected = 0;
		for (int i = 0; i < NUM_DIRS; ++i)
		{
			int wireLen = 0;
			if (TryConnect(coreCnt, i, &wireLen) == 1)
			{
				isConnected = 1;
				DFS(coreCnt + 1, connectCnt + 1, sumWireLen + wireLen);
			}
		}
		if (isConnected == 0)
		{
			DFS(coreCnt + 1, connectCnt, sumWireLen);
		}
		return;
	}
	int CheckBound(const int row, const int col, const int dirIdx)
	{
		return (row + DIR[dirIdx][0] < 0)
			|| (row + DIR[dirIdx][0] >= m_gridSize)
			|| (col + DIR[dirIdx][1] < 0)
			|| (col + DIR[dirIdx][1] >= m_gridSize);
	}
	int CheckNeighbors(const Node_t &node)
	{
		int isBoundary = 0;
		for (int i = 0; i < NUM_DIRS; ++i)
		{
			int row = node.row;
			int col = node.col;
			if (CheckBound(row, col, i) == 1)
			{
				isBoundary = 1;
				break;
			}
		}
		return isBoundary;
	}
	int TryConnect(const int coreCnt, const int dirIdx, int* const pWireLength)
	{
		for (int i = 0; i < NUM_DIRS; i++)
		{
			if (i != dirIdx)
			{
				RemoveConnection(coreCnt, i);
			}
			for (int postCoreIdx = coreCnt + 1; postCoreIdx < m_numCores; postCoreIdx++)
			{
				RemoveConnection(postCoreIdx, i);
			}
		}
		int isConnected = 0;
		int row = m_arNode[coreCnt].row;
		int dRow = DIR[dirIdx][0];
		int col = m_arNode[coreCnt].col;
		int dCol = DIR[dirIdx][1];
		int wireLen = 0;
		for (int i = 0; i < m_gridSize; ++i, row += dRow, col += dCol)
		{
			if (i > 0)
			{
				if (m_matGrid[row][col] != 0)
				{
					break;
				}
				else
				{
					m_matGrid[row][col] = coreCnt + 2;
					wireLen++;
				}
			}
			if (CheckBound(row, col, dirIdx) == 1)
			{
				isConnected = 1;
				break;
			}
		}
		*pWireLength = wireLen;
		return isConnected;
	}
	void RemoveConnection(const int coreCnt, const int dirIdx)
	{
		int row = m_arNode[coreCnt].row;
		int dRow = DIR[dirIdx][0];
		int col = m_arNode[coreCnt].col;
		int dCol = DIR[dirIdx][1];
		for (int i = 0; i < m_gridSize; ++i, row += dRow, col += dCol)
		{
			if (i > 0)
			{
				if (m_matGrid[row][col] != (coreCnt + 2))
				{
					break;
				}
				else
				{
					m_matGrid[row][col] = 0;
				}
			}
			if (CheckBound(row, col, dirIdx) == 1)
			{
				break;
			}
		}
	}
	Node_t m_arNode[MAX_GRID];
};
// Global methods
void ScanGrid(const int gridSize, int(&matGrid)[12][12])
{
	for (int i = 0; i < gridSize; ++i)
	{
		for (int j = 0; j < gridSize; ++j)
		{
			cin >> matGrid[i][j];
		}
	}
}
int ScanTests(CTest* (*ppTest))
{
	int numTests = 0;
	cin >> numTests;
	if (W_IFNOT(numTests > 0))
	{
		*ppTest = new CTest[numTests];
		for (int i = 0; i < numTests; ++i)
		{
			int gridSize = 0;
			int matGrid[MAX_GRID][MAX_GRID];
			cin >> gridSize;
			ScanGrid(gridSize, matGrid);
			(*ppTest)[i].SetGridSize(gridSize);
			(*ppTest)[i].SetGrid(matGrid);
		}
	}
	return numTests;
}
int main()
{
	CTest* pTest = NULL;
	int numTests = ScanTests(&pTest);
	// Solve and print tests
	for (int i = 0; i < numTests; ++i)
	{
		int sumWireLength = pTest[i].ComputeSumWireLength();
		cout << "#" << (i + 1) << " " << sumWireLength << endl;
		// Test prints
// cout << pTest[i].GetGridSize() <<endl;
// pTest[i].PrintGrid();
	}
	delete[] pTest;
	return 0;
}
