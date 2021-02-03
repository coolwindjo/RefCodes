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

typedef long long ll;
constexpr int INF = 987654321;
// #include "../../ProbSolvStart.h"

typedef enum {
	eR=0, eD,
    eL, eU,
    eDIR_LEN
} Dir_e;
constexpr int DIR[eDIR_LEN][2] = {
    {0,1}, {1,0},
    {0,-1}, {-1,0}
};

constexpr int MAX_N = 1e2;
class ProbSolv
{
    int N;
    ii top;
    vvi grid;
    int visit[MAX_N + 10][MAX_N + 10];
public:
    ProbSolv()
    {
        cin >> N;
        cin >> top.first >> top.second;
        FOR(i, N){
            vi rowG;
            FOR(j, N){
                int val;
                cin >> val;
                rowG.push_back(val);
                visit[i][j] = 0;
            }
            grid.push_back(rowG);
        }
#ifdef TEST
        cout <<endl;
        FOR(i, N){
            FOR(j, N){
                cout << grid[i][j] << " ";
            }
            cout <<endl;
        }
#endif
        _Solve();
    }
    ~ProbSolv(){}
private:
    void _Solve(){
        DFS(top, 0);
        cout << minF;
    }

    int minF = INF;
    void DFS(const ii pos, const int f){
        if(f > minF) {
#ifdef TEST
            cout << pos.first << " " << pos.second << "stop!:" << f <<endl;
#endif
            visit[pos.first][pos.second] = 0;
            return;
        }
        if((OOR(pos.first, 0, N-1)) || (OOR(pos.second, 0, N-1))){
            minF = f;
#ifdef TEST
            cout << pos.first << " " << pos.second << "finsh!:" << minF <<endl;
#endif
            visit[pos.first][pos.second] = 0;
            return;
        }
        cout << pos.first << " " << pos.second <<endl;
        visit[pos.first][pos.second] = f;
        FOR(dir, eDIR_LEN){
            ii nextPos(pos.first+DIR[dir][0], pos.second+DIR[dir][1]);
            if (visit[nextPos.first][nextPos.second] != 0) continue;
            int newF = 0;
            int curH = grid[pos.first][pos.second];
            if ((OOR(nextPos.first, 0, N-1)) || (OOR(nextPos.second, 0, N-1))){
                newF = f+((curH)*(curH));
            }
            else{
                int nextH = grid[nextPos.first][nextPos.second];
                if(curH == nextH){
                    newF = f;
                }
                else if(curH > nextH){
                    newF = f+((curH-nextH)*(curH-nextH));
                }
                else{
                    newF = f+(nextH-curH);
                }
            }
            DFS(nextPos, newF);
        }
        visit[pos.first][pos.second] = 0;
    }
};

int main(){
    // ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ProbSolv ps;
    return 0;
}
