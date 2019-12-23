#include <bits/stdc++.h>
using namespace std;

#define FOR_INC(i, from, to) for(int (i)=(from); (i)<(to); ++(i))
#define FOR_DEC(i, from, to) for(int (i)=(to)-1; (i)>=(from); --(i))
#define FOR(i, to) FOR_INC((i), 0, (to))
#define OOR(x, min, max) (((x) < (min)) || ((x) > (max)))

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long ll;
constexpr int INF =987654321;

static const int WarnIfNot(const int condFlag, const char* condition){
    if(condFlag != 0){
        cout << "Warning: [" << condition << "] is violated!\n";
    }
    return condFlag;
}
#define W_IFNOT(cond) WarnIfNot((cond), (#cond))
#define P_IFNOT(cond, var) if(!W_IFNOT(cond)) cout << "= " << var <<endl;

constexpr int NUM_HOUSES = 8;
class CProbSolv
{
    vvi m_dualStates;
    int m_days;
public:
    CProbSolv()
    {
        vi states;
        FOR(s, NUM_HOUSES){
            int state;
            cin >> state;
            states.push_back(state);
        }
        m_dualStates.push_back(states);
        m_dualStates.push_back(states);
        cin >> m_days;
        _Solve();
    }
    ~CProbSolv(){}
private:
    void _Solve(){
        int states[NUM_HOUSES];
        FOR(i, NUM_HOUSES){
            states[i] = m_dualStates[0][i];
        }
        vi viAns = cellCompete(states, m_days);
        FOR(i, NUM_HOUSES){
            cout << viAns[i] << " ";
        }
        cout <<endl;
    }

    vector<int> cellCompete(int* states, int days){
        
         FOR(i, NUM_HOUSES){
            m_dualStates[0][i] = states[i];
        }

        FOR(d, days){
            const int i = d%2;
            const int ni = (d+1)%2;
            FOR(h, NUM_HOUSES){
                if(h == 0){
                    if(m_dualStates[i][h+1] == 0){
                        m_dualStates[ni][h] = 0;
                    }
                    else{
                        m_dualStates[ni][h] = 1;
                    }
                }
                else if(h == (NUM_HOUSES-1)){
                    if(m_dualStates[i][h-1] == 0){
                        m_dualStates[ni][h] = 0;
                    }
                    else{
                        m_dualStates[ni][h] = 1;
                    }
                }
                else{
                    if(m_dualStates[i][h-1] == m_dualStates[i][h+1]){
                        m_dualStates[ni][h] = 0;
                    }
                    else{
                        m_dualStates[ni][h] = 1;
                    }
                }
            }
        }
        const int resIdx = days%2;
        return m_dualStates[resIdx];
    }
};


int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int numTCs = 0;
    cin >> numTCs;
    FOR(tc, numTCs){
        cout << "#" << tc+1 <<" ";
        CProbSolv ps;
    }
    return 0;
}
