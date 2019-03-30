#include <iostream>
#include <queue>

using namespace std;

inline int WarnIfNot(const int condFlag, const char* condition)
{
	if (condFlag == 0)
	{
		cout << "Warn: [" << condition << "] is violoated!\n";
	}
	return condFlag;
}
#define WARN_IFNOT(condition) WarnIfNot((condition), (#condition))

typedef pair<int, int> ii;

static const size_t MAX_NUM_ATOMS = 1000U + 1U;
static const size_t MAX_ENERGY = 100U + 1U;
static const int MAP_QUARTER_SIZE = 1000 + 1;
static const int DIR_NUM = 4;
static const int DIR[DIR_NUM][2] = { {0,1},{0,-1},{-1,0},{1,0} };


class CTest
{
public:
	CTest();
	~CTest();

	void AddAtom(const int x, const int y);

private:
	queue<ii> arAtom;
};

CTest::CTest()
{
}

CTest::~CTest()
{
}

void CTest::AddAtom(const int x, const int y)
{
	WARN_IFNOT(x < MAP_QUARTER_SIZE);
	WARN_IFNOT(x > -MAP_QUARTER_SIZE);
	WARN_IFNOT(y < MAP_QUARTER_SIZE);
	WARN_IFNOT(y > -MAP_QUARTER_SIZE);
	arAtom.push(ii(x, y));
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(nullptr);
	int t;
	cin >> t;

	for (int tc = 1; tc <= t; ++tc)
	{
		cout << "#" << tc << " " << tc << '\n';
	}
	return 0;
}
