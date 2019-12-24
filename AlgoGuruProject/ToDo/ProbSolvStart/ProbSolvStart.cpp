#include "ProbSolvStart.h"

#if 1
#define TEST
#endif // 1

static const int WarnIfNot(const int condFlag, const char* condition){
 	if (condFlag == 0) {
        cout << "Warning: [" << condition << "] is violated!\n";
    }
    return condFlag;
}
#define W_IFNOT(cond) WarnIfNot((cond), (#cond))
#define P_IFNOT(cond, var) if (!W_IFNOT(cond)) cout << "= " << var <<endl;

typedef enum {
	eR=0, eD, eL, eU, eDIR_LEN
} Dir_e;
constexpr int DIR[eDIR_LEN][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };


// constexpr int NUM_HOUSES = 8;
class CProbSolv
{
    // vvi m_vviDualStates;
public:
    CProbSolv()
    {
        _Solve();
    }
    ~CProbSolv(){}
private:
    void _Solve(){

        // vi viStates;
        // FOR(s, NUM_HOUSES){
        //     int state;
        //     cin >> state;
        //     viStates.push_back(state);
        // }
        // m_vviDualStates.push_back(viStates);
        // m_vviDualStates.push_back(viStates);

        // int days = 0;
        // cin >> days;
        // int states[NUM_HOUSES];
        // FOR(i, NUM_HOUSES){
        //     states[i] = viStates[i];
        // }
        // vi viAns = cellCompete(states, days);
        // for(auto ans : viAns){
        //     cout << ans << " ";
        // }
        
    }

    // vector<int> cellCompete(int* states, int days){
    //     const int resIdx = days%2;
    //     return m_vviDualStates[resIdx];
    // }

};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int numTCs = 0;
    cin >> numTCs;
    FOR(tc, numTCs){
        cout << "#" << tc+1 <<" ";
        CProbSolv ps;
        cout << endl;
    }
    return 0;
}
