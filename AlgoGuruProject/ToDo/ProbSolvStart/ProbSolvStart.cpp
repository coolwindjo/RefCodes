#include "../ProbSolvStart.h"

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


class CProbSolv
{
public:
    CProbSolv()
    {
        _Solve();
    }
    ~CProbSolv(){}
private:
    void _Solve(){

#if 0
        int numFeatureRequests = 0;
        cin >> numFeatureRequests;

        vstr featureRequests;
        FOR(i, numFeatureRequests){
            string strFeRe;
            std::getline(std::cin, strFeRe);
            if(strFeRe.length() == 0){
                i--;
                continue;
            }
            featureRequests.push_back(strFeRe);
        }
#endif

#if 0
        int rows = 0;
        int columns = 0;
        cin >> rows;
        cin >> columns;

        vvi grid;
        FOR(i, rows){
            vi rowG;
            FOR(j, columns){
                int val;
                cin >> val;
                rowG.push_back(val);
            }
            grid.push_back(rowG);
        }
#endif
        
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
