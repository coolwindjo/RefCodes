#include <iostream>
#include <vector>

using namespace std;

static const int WarnIfNot(const int condFlag, const char* condition){
    if (condFlag==0){
        cout << "Warning: [" << condition << "] is violated!\n";
    }
    return condFlag;
}
#define W_IFNOT(cond) WarnIfNot((cond), (#cond))
#define P_IFNOT(cond, var) if(!W_IFNOT(cond)) cout << "= " << (var) << endl;
#define FOR_INC(i, from, to) for(int (i)=(from); (i)<(to);++(i))
#define FOR_DEC(i, from, to) for(int (i)=(to)-1; (i)>=(from);--(i))
#define FOR(i, to) FOR_INC((i), 0, (to))
#define OOR(x,min,max) (((x)<(min)) || ((x)>(max)))

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef unsigned long long tUInt;
typedef long long tInt;

typedef enum {
	eR=0, eD, eL, eU, eDIR_LEN
} DIR_e;
constexpr int DIR[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
constexpr int INF = 987654321;  // ~= 2^30

#define TEST
class CProbSolve
{
private:
    /* data */
public:
    explicit CProbSolve(/* args */){}
    virtual ~CProbSolve(){}
    void _Solve(){}
};


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

 	int numTCs = 0;
	cin >> numTCs;
	FOR(tc, numTCs) {

    }

   return 0;
}
