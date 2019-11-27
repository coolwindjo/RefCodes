#if 1
#define TEST
#endif // 1

#ifdef TEST
#include <iostream>
#include <vector>
#else
#include <bits/stdc++.h>
#endif // TEST

using namespace std;

static const int WarnIfNot(const int condFlag, const char* condition){
 	if (condFlag == 0) {
        cout << "Warning: [" << condition << "] is violated!\n";
    }
    return condFlag;
}
#define W_IFNOT(cond) WarnIfNot((cond), (#cond))
#define P_IFNOT(cond, var) if (!W_IFNOT(cond)) cout << "= " << var <<endl;
#define FOR_INC(i, from, to) for(int (i)=(from); (i)<(to); ++(i))
#define FOR_DEC(i, from, to) for(int (i)=(to)-1; (i)>=(from); --(i))
#define FOR(i, to) FOR_INC((i), 0, (to))
#define OOR(x, min, max) (((x)<(min)) || ((x)>(max)))

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long ll;
typedef enum {
	eR=0, eD, eL, eU, eDIR_LEN
} Dir_e;
constexpr int DIR[eDIR_LEN][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
constexpr int INF = 987654321;  // ~= 2^30

class CProbSolve
{
    /* data */
public:
    explicit CProbSolve(/* args */){
        _Solve();
    }
    virtual ~CProbSolve(){}
private:
    void _Solve(){}
};


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

 	int numTCs = 0;
	cin >> numTCs;
	FOR(tc, numTCs) {
 		cout << "#" << tc + 1 << " ";
        CProbSolve ps();
    }

   return 0;
}