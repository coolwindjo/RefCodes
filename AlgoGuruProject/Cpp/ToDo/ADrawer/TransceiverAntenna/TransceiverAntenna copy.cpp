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

typedef vector<int> vi;
// #include "../../ProbSolvStart.h"

constexpr int MAX_N = 1e5;

class ProbSolv
{
    int N;
    int H[MAX_N + 10];
    vi viSt;
public:
    ProbSolv()
    {
        _Solve();
    }
    ~ProbSolv(){}
private:
    void _SolveN2(){
        scanf("%d", &N);
        FOR(i, N){
            scanf("%d", &H[i]);
        }
        int transCnt = 0;
        FOR(i, N){
            int h = 0;
            FOR_INC(j, i+1, N){
                if (h < H[j]){
                    transCnt++;
                    h = H[j];
                }
                if (H[i] <= H[j]) break;
            }
        }
        cout << transCnt;
    }

    void _Solve(){
        scanf("%d", &N);
        FOR(i, N){
            scanf("%d", &H[i]);
        }
        int transCnt = 0;
        FOR(i, N){
            //1.스택Top에 낮은 높이가 있을 때만 pop시키기 & 통신 가능 개수 증가
            while(!viSt.empty()){
                if (viSt.back() >= H[i]) break; 
                transCnt++;
                viSt.pop_back();
            }
            //2.스택에 비어있지 않다면 통신 가능 개수 1 증가
            if (!viSt.empty()){
                transCnt++;
                if (viSt.back() == H[i]) viSt.pop_back();
            }
            //3.i번 높이는 스택에 저장
            viSt.push_back(H[i]);
        }
        cout << transCnt;
    }
};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifdef TEST
    int numTCs = 3;
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