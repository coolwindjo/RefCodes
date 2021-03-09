#if 1
#define TEST
#endif // 1

#include "../../ProbSolvStart.h"

constexpr int MAX_NUM = 8;
class ProbSolv
{
    int N;
    int number;
    int minNumNs;
    std::unordered_set<int> hashM[MAX_NUM + 1];
public:
    ProbSolv()
    {
        cin >> N >> number;
        _Solve();
    }
    ~ProbSolv(){}

    void DFS(const int numNs, const int result){
        if (numNs > MAX_NUM) return;
        if (numNs >= minNumNs) return;

        if (result == number) {
            minNumNs = numNs;
        }

        hashM[numNs].insert(result);

        int NN = 0;
        FOR(i, MAX_NUM){
            int nextNumNs = numNs + i + 1;
            if (nextNumNs > MAX_NUM) break;

            NN = NN*10 + N;
            int plus = NN + result;
            int minus = NN - result;
            int mult = NN * result;

            if (hashM[nextNumNs].find(plus)==hashM[nextNumNs].end()){
                DFS((nextNumNs), (plus));
            }
            if (hashM[nextNumNs].find(minus)==hashM[nextNumNs].end()){
                DFS((nextNumNs), (minus));
            }
            if (hashM[nextNumNs].find(-1*minus)==hashM[nextNumNs].end()){
                DFS((nextNumNs), (-1*minus));
            }
            if (hashM[nextNumNs].find(mult)==hashM[nextNumNs].end()){
                DFS((nextNumNs), (mult));
            }
            if (result != 0) {
                int divid = NN / result;
                if (hashM[nextNumNs].find(divid)==hashM[nextNumNs].end()){
                    DFS((nextNumNs), (divid));
                }
            }
            if (NN != 0) {
                int r_divid = result / NN;
                if (hashM[nextNumNs].find(r_divid)==hashM[nextNumNs].end()){
                    DFS((nextNumNs), (r_divid));
                }
            }
        }
    }

    int DP(){
        int minNumNs = MAX_NUM + 1;
        int NN = 0;
        FOR(i, MAX_NUM){
            int I = i+1;
            NN = NN*10 + N; // 5, 55, 555, ... , 55555555
            hashM[I].insert(NN);
            hashM[I].insert(-1*NN);
            FOR(j, i){
                int J = j+1;
                int K = (i-j);    // I:J:K = i+1:j+1:i-j, 2:1:1
                                  //                    , 3:1:2, 3:2:1
                for(auto itJ = hashM[J].begin();
                itJ!=hashM[J].end(); ++itJ){
                    for(auto itK = hashM[K].begin();
                    itK!=hashM[K].end(); ++itK){
                        hashM[I].insert(*itJ + *itK);
                        hashM[I].insert(*itJ - *itK);
                        hashM[I].insert(*itJ * *itK);
                        if (*itK != 0) hashM[I].insert(*itJ / *itK);
                    }
                }
            }
            if (hashM[I].find(number) != hashM[I].end()) {
                minNumNs = I;
                break;
            }
        }
        return  minNumNs;
    }

private:
    void _Solve(){
        minNumNs = MAX_NUM+1;
        DFS(0, 0);
        // minNumNs = DP();
        if (minNumNs == MAX_NUM+1) {
            minNumNs = -1;
        }
        cout << minNumNs;
    } // _Solve()

};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int numTCs = 0;
    cin >> numTCs;
    FOR (tc, numTCs) {
        cout << "#" << tc+1 <<" ";
        ProbSolv ps;
        cout << endl;
    }
    return 0;
}
