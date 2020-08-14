#include "../../ProbSolvStart.h"

constexpr int MAX = 3e4;
struct num_grade
{
    int stuN;
    int gradeN;
};

class ProbSolv
{
    int N;
    num_grade a[MAX + 10];
public:
    ProbSolv()
    {
        // _SolveC();
        _SolveCpp();
    }
    ~ProbSolv(){}
private:
    void _SolveC(){
        scanf("%d", &N);
        FOR(i, N){
            a[i].stuN = i+1;
            scanf("%d", &a[i].gradeN);
        }
        qsort(a, N, sizeof(num_grade), _CompareC);
        FOR(i, 3){
            // cout << a[i].stuN << " : " << a[i].gradeN << endl;
            cout << a[i].stuN << " ";
        }
    }
    void _SolveCpp(){
        scanf("%d", &N);
        FOR(i, N){
            a[i].stuN = i+1;
            scanf("%d", &a[i].gradeN);
        }
        sort(&a[0], &a[N], _CompareCpp);
        FOR(i, 3){
            // cout << a[i].stuN << " : " << a[i].gradeN << endl;
            cout << a[i].stuN << " ";
        }
    }
    static int _CompareC(const void* a, const void* b){
        int diff = (((num_grade*)b)->gradeN - ((num_grade*)a)->gradeN);
        if (diff == 0) {
            return (((num_grade*)a)->stuN - ((num_grade*)b)->stuN);
        }
        return diff;
    }
    static bool _CompareCpp(num_grade a, num_grade b){
        int diff = (b.gradeN < a.gradeN);
        if (diff == 0) {
            return (b.gradeN < a.gradeN);
        }
        return diff;
    }

};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ProbSolv ps;
    return 0;
}
