#include <iostream>
#include <vector>

using namespace std;

inline static const int WarnIfNot(const int condFlag, const char* condition){
    if (condFlag==0){
        cout << "Warning: [" << condition << "] is violated!\n";
    }
    return condFlag;
}
#define W_IFNOT(cond) WarnIfNot((cond), (#cond))
#define P_IFNOT(cond, var) if(!W_IFNOT(cond)) cout << "= " << (var) << endl;
#define FOR_INC(i, from, to) for(int (i)=(from); (i)<(to); (i)++)
#define FOR_DEC(i, from, to) for(int (i)=(to)-1; (i)>=(from); (i)--)
#define FOR(i, to) FOR_INC((i),0,(to))
#define OOR(val, min, max) ((val)<(min))||((val)>(max))

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef unsigned long long tUInt;
typedef long long tInt;

const int INF = 1e9;

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

    return 0;
}
