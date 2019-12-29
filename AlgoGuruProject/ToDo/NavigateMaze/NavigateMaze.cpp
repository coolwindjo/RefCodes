#include "../../ProbSolvStart.h"

class CNode
{
	int m_x;
	int m_y;
	int m_val;

public:
	CNode();
	CNode(int x, int y);
	~CNode() {}
	int X() { return m_x; }
	int Y() { return m_y; }
	int GetValue() { return m_val; }
	void SetValue(int x, int y, int val)
	{
		m_x = x;
		m_y = y;
		m_val = val;
	}
	void SetVisit(int currStep)
	{
		m_val = currStep + 1;
		m_visited = 1;
	}
	int CheckBoundary(int xBound, int yBound)
	{
		int ret = 0;
		if (m_x<0 || m_x>=xBound
			|| m_y<0 || m_y>=yBound)
		{
			ret = 1;
		}

		return ret;
	}
	int CheckCanGo() { return static_cast<int>(m_val && !m_visited); }

private:
	int m_visited;

};

queue<CNode> nodeQ;
int moveXY[4][2] = {
	0,-1,
	0,+1,
	-1,0,
	+1,0
};

CNode::CNode()
{
	m_visited = 0;
	m_val = 0;
}

CNode::CNode(int x, int y):CNode()
{
	m_x = x;
	m_y = y;
}
CNode** arMap;

int BFS(int x, int y, int xBound, int yBound)
{
	int numSteps = 0;

	CNode* pRootNode = &arMap[x][y];
	pRootNode->SetVisit(0);
	nodeQ.push(*pRootNode);

	int maxLoop = xBound * yBound;
	for (int i = 0; !nodeQ.empty() && (i < maxLoop); i++)
	{
		CNode* pCurrNode = &nodeQ.front();
		nodeQ.pop();
		//printf("CurrNode: %d, %d, %d\n", pCurrNode->X(), pCurrNode->Y(), pCurrNode->GetValue());
		for (int j = 0; j < 4; j++)
		{
			// Guard clauses
			CNode movedNode(pCurrNode->X() + moveXY[j][0], pCurrNode->Y() + moveXY[j][1]);
			if (movedNode.CheckBoundary(xBound, yBound) == 1)
			{
				continue;
			}

			CNode* pNodeOnMap = &(arMap[movedNode.X()][movedNode.Y()]);
			if (pNodeOnMap->CheckCanGo() == 0)
			{
				continue;
			}

			pNodeOnMap->SetVisit(pCurrNode->GetValue());
			//printf("Add NextNode: %d, %d, %d\n", pNodeOnMap->X(), pNodeOnMap->Y(), pNodeOnMap->GetValue());
			nodeQ.push(*pNodeOnMap);
		}
	}
	numSteps = arMap[xBound - 1][yBound - 1].GetValue();

	return numSteps;
}

using namespace std;

int main()
{
	int m = 0;
	int n = 0;
	size_t N = 0;
	cin >> N;

	string strLine;
	for(size_t test_case = 0; test_case < N; test_case++)
	{
		cin >> m >> n;
		getline(cin, strLine);

		arMap = new CNode*[m];
		for (int i = 0; i < m; i++)
		{
			arMap[i] = new CNode[n];
			getline(cin, strLine);
			for (int j = 0; j < n; j++)
			{
				int oneOrZero = strLine.at(j) - '0';
				arMap[i][j].SetValue(i, j, oneOrZero);
			}
		}

		int numSteps = BFS(0, 0, m, n);

		printf("%d\n", numSteps);

		for (int i = 0; i < m; i++)
		{
			delete[] arMap[i];
		}
		delete[] arMap;
	}
	
	return 0;
}
