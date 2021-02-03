#include "../../ProbSolvStart.h"

static const int MAX_NUM_CHARS_PER_SIDE = 7 + 1;
static const int MAX_NUM_CHARS = 28 + 1;
static const int HEX_DEC = 16;

typedef struct
{
	int arrayEnd;
	char arszHexDecNum[MAX_NUM_CHARS][MAX_NUM_CHARS_PER_SIDE];	// <number of chars per side> - long strings can be added up to <number of chars>
} StringHash_t;

class CTest
{
	StringHash_t m_arstHash[HEX_DEC];
public:
	explicit CTest()
	{
		for (int i = 0; i < HEX_DEC; ++i)
		{
			m_arstHash[i].arrayEnd = 0;
			for (int j = 0; j < MAX_NUM_CHARS; ++j)
			{
				for (int k = 0; k < MAX_NUM_CHARS_PER_SIDE; ++k)
				{
					m_arstHash[i].arszHexDecNum[j][k] = '\0';
				}
			}
		}
	}
	virtual ~CTest() {}

	int GetDecimal(char c)
	{
		int decNum = 0;
		if (c < 'A')
		{
			decNum = c - '0';
		}
		else
		{
			decNum = 10 + (c - 'A');
		}
		return decNum;
	}

	void CpyStr(const char a[], const int numChars, char b[], const int numWholeChars = 0)
	{
		for (int i = 0; i < numChars; ++i)
		{
			if ((numWholeChars != 0) && (a[i] == '\0'))
			{
				b[i] = a[(i - numWholeChars)];	// wraparound
			}
			else
			{
				b[i] = a[i];
			}
		}
		b[numChars] = '\0';
	}
	int CmpStr(const char a[], const char b[], const int numChars)
	{
		int retVal = 0;
		for (int i = 0; i < numChars; i++)
		{
			retVal = (a[i] - b[i]);
			if (retVal != 0)
			{
				break;
			}
		}

		return retVal;
	}

	long long FindKthLargest(const char(&arcHexDecString)[MAX_NUM_CHARS], const int K, const int N)
	{
		int n = N / 4;

		for (int i = 0; i < N; ++i)
		{
			char c = arcHexDecString[i];
			int index = GetDecimal(c);
			char arcHexDecNum[MAX_NUM_CHARS_PER_SIDE];
			CpyStr(&arcHexDecString[i], n, arcHexDecNum, N);
			AddToHash(arcHexDecNum, n, index);
		}

		int largestCnt = 0;
		int hashIdx = 0;
		for (int i = (HEX_DEC - 1); i >= 0; --i)
		{
			largestCnt += m_arstHash[i].arrayEnd;
			if (largestCnt >= K)
			{
				hashIdx = i;
				break;
			}
		}
		int KstIdxInArray = (largestCnt - K);	// If largestCnt == K, the first one is the Kth largest.
		return ComputeDecimal(m_arstHash[hashIdx].arszHexDecNum[KstIdxInArray], n);
	}
	void AddToHash(const char(&arcHexDecNum)[MAX_NUM_CHARS_PER_SIDE], const int n, const int index)
	{
		int arrayIdx = 0;
		for (int i = 0; i < m_arstHash[index].arrayEnd; ++i, arrayIdx = i)
		{
			int PosMeansFirstIsBigger = 0;
			if ((PosMeansFirstIsBigger = CmpStr(m_arstHash[index].arszHexDecNum[i], arcHexDecNum, n)) == 0)
			{
				return;
			}
			else if (PosMeansFirstIsBigger > 0)
			{
				// Shift up the upper list and make increasing sorted array
				for (int j = m_arstHash[index].arrayEnd - 1; j >= i; --j)
				{
					CpyStr(m_arstHash[index].arszHexDecNum[j], n, m_arstHash[index].arszHexDecNum[j + 1]);
				}
				arrayIdx = i;
				break;
			}
			else{}	// Do nothing
		}
		CpyStr(arcHexDecNum, n, m_arstHash[index].arszHexDecNum[arrayIdx]);
		m_arstHash[index].arrayEnd++;
	}
	long long ComputeDecimal(const char(&arcHexDecNum)[MAX_NUM_CHARS_PER_SIDE], const int n)
	{
		long long decNum = 0;
		for (int i = 0; i < n; i++)
		{
			decNum = (decNum << 4) + GetDecimal(arcHexDecNum[i]);
		}
		return decNum;
	}

};

char g_arcInputHexDecString[MAX_NUM_CHARS];

int main(int argc, char** argv)
{
	int test_case = 0;
	int T = 0;

    cin >> T;
	for (test_case = 1; test_case <= T; ++test_case)
	{

		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			 이 부분에 여러분의 알고리즘 구현이 들어갑니다.
		 */
		 /////////////////////////////////////////////////////////////////////////////////////////////
		CTest test;
		int N = 0;
		int K = 0;
		cin >> N >> K >> g_arcInputHexDecString;
		cout << "#" << test_case << " " << test.FindKthLargest(g_arcInputHexDecString, K, N) << endl;

	}

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}