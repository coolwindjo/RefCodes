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

typedef enum {
	eR=0, eD,
    eL, eU,
    eDIR_LEN
} Dir_e;
constexpr int DIR[eDIR_LEN][2] = {
    {0,1}, {1,0},
    {0,-1}, {-1,0}
};

class ProbSolv
{
    int rows = 0;
    int columns = 0;
    vvi grid;
    vii viiStartPt;
public:
    ProbSolv()
    {
        cin >> rows;
        cin >> columns;

        FOR(i, rows){
            vi rowG;
            FOR(j, columns){
                int val;
                cin >> val;
                if(val == 1){
                    if((j == 0) || (!rowG.empty() && rowG.back() == 0)){
                        viiStartPt.push_back(ii(i, j));
                    }
                }
                rowG.push_back(val);
            }
            grid.push_back(rowG);
        }
        _Solve();
        FOR(i, rows){
            FOR(j, columns){
                cout << grid[i][j] << " ";
            }
            cout <<endl;
        }
    }
    ~ProbSolv(){}
private:
    void _Solve(){
        while(!viiStartPt.empty()){
            const ii startPt = viiStartPt.back(); viiStartPt.pop_back();
            int cnt = 1;
            FOR_INC(i, startPt.second, columns){
                if(grid[startPt.first][i] == 1){
                    grid[startPt.first][i] = cnt++;
                }
                else{
                    break;
                }
            }
        }
    }

};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ProbSolv ps;
    return 0;
}
