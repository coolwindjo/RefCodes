#if 0
#define TEST
#endif // 1

#include <bits/stdc++.h>
using namespace std;

#define FOR_INC(i, from, to) for(int (i)=(from); (i)<(to); ++(i))
#define FOR_DEC(i, from, to) for(int (i)=(to)-1; (i)>=(from); --(i))
#define FOR(i, to) FOR_INC((i), 0, (to))
#define OOR(x, min, max) (((x) < (min) || (x) > (max)))

static const int WarnIfNot(const int condFlag, const char* condition){
 	if (condFlag == 0) {
        cout << "Warning: [" << condition << "] is violated!\n";
    }
    return condFlag;
}
#define W_IFNOT(cond) WarnIfNot((cond), (#cond))
#define P_IFNOT(cond, var) if (!W_IFNOT(cond)) cout << "= " << var <<endl;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, ii> i_ii;
typedef queue<ii> qii;
typedef queue<int> qi;
typedef priority_queue<ii> pqii;
// #include "../../ProbSolvStart.h"

constexpr int MAX_N = 1e5;
constexpr int MAX_R = 1e8;
class ProbSolv
{
    int N;
    vii viiBeginEnd;
public:
    ProbSolv()
    {
        _Solve();
    }
    ~ProbSolv(){}
private:
    void _Solve(){
        scanf("%d", &N);
        FOR(i, N){
            int begin, end;
            scanf("%d %d", &begin, &end);
            viiBeginEnd.push_back(ii(begin, end));
        }
        sort(viiBeginEnd.begin(), viiBeginEnd.end(), comp);
        int cnt = 0;
        while(!viiBeginEnd.empty()){
            ii cur = viiBeginEnd.back(); viiBeginEnd.pop_back();
            cnt++;
            while(!viiBeginEnd.empty() && cur.second >= viiBeginEnd.back().first){
                // pop any cinema starting before current end
                viiBeginEnd.pop_back();
            }
        }
        cout << cnt;
    }
    static bool comp(ii a, ii b){
        return a.second > b.second;
    }

};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifdef TEST
    int numTCs = 0;
    cin >> numTCs;
    FOR(tc, numTCs){
        cout << "#" << tc+1 <<" ";
#endif
        ProbSolv ps;
#ifdef TEST
        cout << endl;
    }
#endif
    return 0;
}
