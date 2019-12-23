#include <bits/stdc++.h>
using namespace std;

#define FOR_INC(i, from, to) for(int (i)=(from); (i)<(to); ++(i))
#define FOR_DEC(i, from, to) for(int (i)=(to)-1; (i)>=(from); --(i))
#define FOR(i, to) FOR_INC((i), 0, (to))
#define OOR(x, min, max) (((x) < (min) || (x) > (max)))

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long ll;
constexpr int INF = 987654321;

class IProbSolv
{
public:
    explicit IProbSolv(){}
    virtual ~IProbSolv(){}
    void Solve(){
        cout << typeid(*this).name() << ":\n";
        _Solve();
        cout << "\n";
   }
private:
    virtual void _Solve() = 0;
};
