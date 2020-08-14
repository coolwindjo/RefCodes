#if 1
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
typedef queue<i_ii> qi_ii;
typedef queue<int> qi;
// #include "../../ProbSolvStart.h"

#if 1
typedef enum {
	eR=0, eD,
    eL, eU,
    eDIR_LEN
} Dir_e;
constexpr int DIR[eDIR_LEN][2] = {
    {0,1}, {1,0},
    {0,-1}, {-1,0}
};
#endif // 0

constexpr int MAX_M = 1e3;
constexpr int MAX_N = 1e3;

class ProbSolv
{
    int M;
    int N;
    vvi grid; // 0->1 -1:empty
    vii startPts;
    qi_ii qi_iiBFS;
public:
    ProbSolv()
    {
        _Solve();
    }
    ~ProbSolv(){}
private:
    void _Solve(){

        int rows = 0;
        int columns = 0;
        cin >> columns; // M
        cin >> rows;    // N
        M = columns;
        N = rows;
        FOR(i, rows){
            vi rowG;
            FOR(j, columns){
                int val;
                cin >> val;
                rowG.push_back(val);
                if(val == 1){
                    startPts.push_back(ii(i, j));
                }
            }
            grid.push_back(rowG);
        }
#ifdef TEST
        cout <<endl;
        FOR(i, rows){
            FOR(j, columns){
                cout << grid[i][j] << " ";
            }
            cout <<endl;
        }
#endif
        while(!startPts.empty()){
            const ii start = startPts.back(); startPts.pop_back();
            qi_iiBFS.push_back(i_ii(0, start));
        }
        _BFS();
         
    }
    int _BFS(){
        while(!qi_iiBFS.empty()){
            const i_ii cur = qi_iiBFS.front(); qi_iiBFS.pop();
            FOR(dir,eDIR_LEN){
                ii next;
                next.first = cur.second.first + DIR[dir][0];
                next.second = cur.second.second + DIR[dir][1];
                if(OOR(next.first, 0, M)) continue;
                if(OOR(next.second, 0, N)) continue;
                qi_iiBFS.push_back(i_ii(cur.first+1, next);
            }
        }
    }

};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifdef TEST
    int numTCs = 3;
    // cin >> numTCs;
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
