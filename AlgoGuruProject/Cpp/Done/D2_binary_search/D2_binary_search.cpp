#include "../../ProbSolvStart.h"
constexpr int MAX_N = 5e4;
constexpr int MAX_T = 1e4;

class ProbSolv
{
    int N;
    int data[MAX_N+10];
    int T;
    int key[MAX_T+10];
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
            scanf("%d", &data[i]);
        }
        scanf("%d", &T);
        FOR(i, T){
            scanf("%d", &key[i]);
        }
        FOR(i, T){
            const int keyNum = key[i];
            const int num = _BinSearchLoop(0, N-1, keyNum, data);
            // const int num = _BinSearchRecur(0, N, keyNum, data);
            cout << num+1 <<endl;
        }
    }
    int _BinSearchLoop(const int begin, const int end, const int key, const int (&data)[MAX_N+10]){
        int b = begin;
        int e = end;
        while(b <= e) { // begin~end
            const int h = (int)(b+e)*0.5F;
            if (data[h] == key){
                return h;
            }
            else if (data[h] > key){
                e = h-1;
            }
            else {
                b = h+1;
            }
        }
        return -1;
    }
    int _BinSearchRecur(const int begin, const int end, const int key, const int (&data)[MAX_N+10]){
        if (begin >/*=*/ end){ // begin~end-1
            return -1;
        }
        const int halfIdx = (int)((begin + end) * 0.5F);
        if (data[halfIdx] == key){
            return halfIdx;
        }
        else if (data[halfIdx] > key){
            return _BinSearchRecur(begin, halfIdx/*-1*/, key, data);
        }
        else {
            return _BinSearchRecur(halfIdx+1, end, key, data);
        }
    }

};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ProbSolv ps;
    return 0;
}
