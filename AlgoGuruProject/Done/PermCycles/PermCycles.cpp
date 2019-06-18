#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

const int WarnIfNot(const int condFlag, const char* condition){
    if (condFlag == 0){
        cout << "Warning: [" << condition << "] is violated!\n";
    }
    return condFlag;
}
#define W_IFNOT(condition) WarnIfNot((condition), (#condition))
#define P_IFNOT(cond, var) if(!W_IFNOT((cond))) cout << "= " << (var) <<endl;
#define FOR_INC(i, from, to) for(int (i)=(from); (i)<(to); (i)++)
#define FOR(i, to) FOR_INC((i), 0, (to))

typedef vector<int> vi;
typedef unordered_set<int> usi;

const int MAX_N = 1000+1;

class CProvSolv
{
    int m_N;
    vi m_viPerm;
    usi m_usiPerm;

public:
    explicit CProvSolv(const int N){
        m_N = N;
        FOR(i, m_N){
            int permNum=0;
            cin >> permNum;
            P_IFNOT(permNum>0, permNum);
            m_viPerm.push_back(permNum);
            m_usiPerm.insert(permNum);
        }

        Solve();
    }
    virtual ~CProvSolv(){}

    void Solve(){
        int cycleCnt = 0;
        FOR(i, m_N){
            usi::iterator it = m_usiPerm.find(i+1);
            if(it == m_usiPerm.end()){
                continue;
            }
            m_usiPerm.erase(it);

            if (m_viPerm.at(i) == i+1){
                cycleCnt++;
            }
            else{
                int nodeFrom = i+1;
                int nodeTo = m_viPerm.at(nodeFrom-1);
                while(nodeTo != (i+1)){
                    usi::iterator delit = m_usiPerm.find(nodeTo);
                    if(W_IFNOT(delit != m_usiPerm.end()));
                    else {
                        break;
                    }
                    m_usiPerm.erase(delit);
                    nodeFrom = nodeTo;
                    nodeTo = m_viPerm.at(nodeFrom-1);
                    P_IFNOT(nodeTo <= m_N, nodeTo);
                }
                cycleCnt++;
            }
        }

        cout << cycleCnt;
    }
    
};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int numTCs=0;
    cin >> numTCs;
    P_IFNOT(numTCs > 0, numTCs);
    FOR(i, numTCs){
        int N=0;
        cin >> N;
        P_IFNOT(N > 0, N);
        CProvSolv ps(N);
        cout << endl;
    }
}