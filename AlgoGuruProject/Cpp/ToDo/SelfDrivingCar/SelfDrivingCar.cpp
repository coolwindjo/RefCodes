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

class ProbSolv
{
    int H;//세로크기
    int W;//가로크기
    char map[500][510];//지도

    void input_data(){
        int i;
        cin >> H >> W;
        for(i=0 ; i<H ; i++){
            cin >> map[i];
        }
    }

public:
    ProbSolv()
    {
        _Solve();
    }
    ~ProbSolv(){}
private:
    void _Solve(){
        int ans = 0;
        input_data();

        
        
        cout << ans << endl;
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
