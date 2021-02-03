#if 1
#define TEST
#endif // 1
#include <bits/stdc++.h>
using namespace std;

#define FOR_INC(i, from, to) for(int (i)=(from); (i)<(to); ++(i))
#define FOR_DEC(i, from, to) for(int (i)=(to)-1; (i)>=(from); --(i))
#define FOR(i, to) FOR_INC((i), 0, (to))

typedef pair<int, int> ii;
typedef pair<int, ii> i_ii;
typedef vector<i_ii> vi_ii;

constexpr int MAX_N = 1e3;
constexpr int MAX_P = 1e8;

class ProbSolv
{
    int N;
    int P[MAX_N + 10];
    vi_ii vi_iiCases;
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
            scanf("%d", &P[i]);
        }
        sort(P, P+N);
#ifdef TEST
        FOR(i, N){
            cout << P[i] <<endl;
        }
#endif
        FOR(i, N-2){
            const int start = P[i];
            FOR_INC(j, i+1, N-1){
                const int middle = P[j];
                const int minP = (middle - start) + middle;
                const int maxP = 2*(middle - start) + middle;
                int minIdx = j+1;
                const int lowIdx = _BinSearch(minIdx, N-1, minP, P);
                if (lowIdx < 0) break;
                const int upIdx = _BinSearch(lowIdx, N-1, maxP, P);
                if (upIdx < 0) break;
                FOR_INC(k, lowIdx, upIdx+1){
                    const int finish = P[k];
                    vi_iiCases.push_back(i_ii(start, ii(middle,finish)));
                }
                // FOR_INC(k, minP, maxP+1){
                // }
            }
        }
        cout << vi_iiCases.size();
#ifdef TEST
        FOR(i, vi_iiCases.size()){
            cout << "(" << vi_iiCases[i].first << ", " << vi_iiCases[i].second.first << ", " << vi_iiCases[i].second.second << ")";
            if (i < vi_iiCases.size()-1){
                cout << ", ";
            }
        }
#endif
    }
    int _BinSearch(const int begin, const int end, const int key, const int (&P)[MAX_N+10]){
        int b = begin;
        int e = end;
        while (b <= e) {
            const int h = (int) (b+e)*0.5F;
            if (P[h] == key) {
                return h;
            }
            else if (P[h] > key) {
                e = h-1;
            }
            else {
                b = h+1;
            }
        }
        return -1;
    }

};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ProbSolv ps;
    return 0;
}
