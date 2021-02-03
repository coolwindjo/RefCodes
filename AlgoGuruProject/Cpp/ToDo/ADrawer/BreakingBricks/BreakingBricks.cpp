#include "../../ProbSolvStart.h"

const size_t MAX_NUM_BALLS = (4U + 1U);
const size_t MAX_NUM_ROWS = (15U + 1U);
const size_t MAX_NUM_COLS = (12U + 1U);
const size_t MAX_NUM_BRICKS = MAX_NUM_ROWS * MAX_NUM_COLS;
const size_t NUM_DIRS = 4U;
const int DIR[NUM_DIRS][2] = { { 1,0 },{ 0,1 },{ -1,0 },{ 0,-1 } };

class CTest
{
	int m_N_numBalls;
	size_t m_W_numBrickCols;
	size_t m_H_numBrickRows;
	int m_matMap[MAX_NUM_BALLS][MAX_NUM_ROWS][MAX_NUM_COLS];

public:

	CTest(const int N, const size_t W, const size_t H);
	~CTest();

	int SetMapValue(const size_t rowIdx, const size_t colIdx, const int value);
	void PrintMap();
	int SimulateBreakingBricks();
	void DFSforBallDrop(const int ballNum, const int remainedNumBricks);
	void DFSforBrickRemoval(const size_t rowIdxToStart, const size_t colIdxToStart,
							int &numRemovedBricksOut, int(&matMapOut)[MAX_NUM_ROWS][MAX_NUM_COLS]);
	size_t FindUpperMostBrickIndex(const int(&matMap)[MAX_NUM_ROWS][MAX_NUM_COLS], const size_t colIdx);
	const int RemoveBrick(const size_t rowIdx, const size_t colIdx,
						  int &numRemovedBricksOut, int(&matMapOut)[MAX_NUM_ROWS][MAX_NUM_COLS]);
	int FallBricksAndFillEmptySpace(const int numRemovedBricks, int(&matMapOut)[MAX_NUM_ROWS][MAX_NUM_COLS]);

private:
	int m_inputNumBricks;
	int m_minRemainedNumBricks;
};

CTest::CTest(const int N, const size_t W, const size_t H)
	: m_N_numBalls(N)
	, m_W_numBrickCols(W)
	, m_H_numBrickRows(H)
	, m_inputNumBricks(0)
	, m_minRemainedNumBricks(MAX_NUM_BRICKS)
{
	(void)memset(&m_matMap[0][0][0], 0, sizeof(m_matMap));
}

CTest::~CTest()
{
}

int CTest::SetMapValue(const size_t rowIdx, const size_t colIdx, const int value)
{
	if (!W_IFNOT(rowIdx < MAX_NUM_ROWS)
		|| !W_IFNOT(colIdx < MAX_NUM_COLS)
		|| !W_IFNOT(value >= 0 && value <= 9))
	{
		return -1;
	}

	m_matMap[0][rowIdx][colIdx] = value;

	if (value > 0)
	{
		m_inputNumBricks++;
	}

	return 0;
}

void CTest::PrintMap()
{
	for (size_t i = 0; i < m_H_numBrickRows; i++)
	{
		for (size_t j = 0; j < m_W_numBrickCols; j++)
		{
			cout << m_matMap[0][i][j];
		}
		cout << endl;
	}
}

int CTest::SimulateBreakingBricks()
{
	if (!W_IFNOT(m_W_numBrickCols > 0) || !W_IFNOT(m_H_numBrickRows > 0))
	{
		return -1;
	}

	m_minRemainedNumBricks = m_inputNumBricks;
	DFSforBallDrop(1, m_inputNumBricks);

	W_IFNOT(m_minRemainedNumBricks < m_inputNumBricks);

	return m_minRemainedNumBricks;
}

void CTest::DFSforBallDrop(const int ballNum, const int remainedNumBricks)
{
	// Basis part
	if (!W_IFNOT(remainedNumBricks >= 0))
	{
		m_minRemainedNumBricks = 0;
		return;
	}
	if (remainedNumBricks == 0)
	{
		m_minRemainedNumBricks = 0;
		return;
	}
	if (ballNum > m_N_numBalls)
	{
		if (remainedNumBricks < m_minRemainedNumBricks)
		{
			m_minRemainedNumBricks = remainedNumBricks;
#ifdef TEST
			PrintMap();
			cout << endl;
#endif // TEST
		}
		return;
	}

	// Inductive part
	for (size_t colIdx = 0; colIdx < m_W_numBrickCols; colIdx++)
	{
		(void)memcpy(&m_matMap[ballNum][0][0], &m_matMap[ballNum - 1][0][0], sizeof(m_matMap[ballNum]));

		// Get an initial brick column index to be broken
		const size_t initRowIdx = FindUpperMostBrickIndex(m_matMap[ballNum], colIdx);

		int numRemovedBricks = 0;
		DFSforBrickRemoval(initRowIdx, colIdx,
						   numRemovedBricks, m_matMap[ballNum]);

		if (numRemovedBricks > 0)
		{
			int numProcessedBricks = FallBricksAndFillEmptySpace(numRemovedBricks,
																 m_matMap[ballNum]);
			W_IFNOT(numProcessedBricks == numRemovedBricks);

			DFSforBallDrop((ballNum + 1), (remainedNumBricks - numProcessedBricks));
		}
	}

}

size_t CTest::FindUpperMostBrickIndex(const int(&matMap)[MAX_NUM_ROWS][MAX_NUM_COLS], const size_t colIdx)
{
	size_t foundRowIdx = 0;
	for (size_t i = 0; i < m_H_numBrickRows; i++)
	{
		if (matMap[i][colIdx] > 0)
		{
			foundRowIdx = i;
			break;
		}
	}
	return foundRowIdx;
}

void CTest::DFSforBrickRemoval(const size_t rowIdxToStart, const size_t colIdxToStart,
							   int &numRemovedBricksOut, int(&matMapOut)[MAX_NUM_ROWS][MAX_NUM_COLS])
{
	// Basis part
	int brickValue = 0;
	if (!W_IFNOT((brickValue = RemoveBrick(rowIdxToStart, colIdxToStart, numRemovedBricksOut, matMapOut)) >= 0))
	{
		return;
	}

	// Inductive part
	if (brickValue > 1)
	{
		for (size_t dirIdx = 0; dirIdx < NUM_DIRS; dirIdx++)
		{
			for (int i = 1; i < brickValue; i++)
			{
				const size_t rowIdx = (rowIdxToStart + i * DIR[dirIdx][0]);
				const size_t colIdx = (colIdxToStart + i * DIR[dirIdx][1]);
				if ((rowIdx < m_H_numBrickRows) && (colIdx < m_W_numBrickCols))
				{
					DFSforBrickRemoval(rowIdx, colIdx, numRemovedBricksOut, matMapOut);
				}
			}
		}
	}
}

const int CTest::RemoveBrick(const size_t rowIdx, const size_t colIdx,
							 int &numRemovedBricksOut, int(&matMapOut)[MAX_NUM_ROWS][MAX_NUM_COLS])
{
	// Guard clauses
	if (!W_IFNOT(rowIdx < m_H_numBrickRows)
		|| !W_IFNOT(colIdx < m_W_numBrickCols))
	{
		return -1;
	}

	const int brickValue = matMapOut[rowIdx][colIdx];
	if (brickValue == 0)
	{
		return 0;
	}

	if (brickValue < 0)
	{
		return 0;
	}
	numRemovedBricksOut++;

	matMapOut[rowIdx][colIdx] = -1;

	return brickValue;
}

int CTest::FallBricksAndFillEmptySpace(const int numRemovedBricks, int(&matMapOut)[MAX_NUM_ROWS][MAX_NUM_COLS])
{
	int brickCnt = 0;
	for (size_t colIdx = 0; colIdx < m_W_numBrickCols; colIdx++)
	{
		int rowIdxFromBottom = 0;
		for (int rowIdx = ((int)m_H_numBrickRows - 1); rowIdx >= 0; --rowIdx)
		{
			const int upperBrickValue = matMapOut[rowIdx][colIdx];
			if (upperBrickValue < 0)
			{
				if (rowIdxFromBottom == 0)
				{
					rowIdxFromBottom = rowIdx;
				}
				matMapOut[rowIdx][colIdx] = 0;
				brickCnt++;
			}
			else
			{
				if (rowIdxFromBottom > 0)
				{
					matMapOut[rowIdx][colIdx] = matMapOut[rowIdxFromBottom][colIdx];
					matMapOut[rowIdxFromBottom--][colIdx] = upperBrickValue;
				}
			}

		}

	}

	return brickCnt;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		int N = 0, W = 0, H = 0;
		cin >> N >> W >> H;
		CTest test(N, W, H);
		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
			{
				int value;
				cin >> value;
				test.SetMapValue(i, j, value);
			}
		}

#ifdef TEST
		test.PrintMap();
#endif // TEST

		cout << "#" << test_case << " " << test.SimulateBreakingBricks() << endl;

	}

#ifdef TEST
	getchar();
#endif // TEST

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
