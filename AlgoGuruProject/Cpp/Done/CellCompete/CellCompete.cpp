#include "../../ProbSolvStart.h"

constexpr int NUM_HOUSES = 8;
class ProbSolv
{
    vvi m_vviDualStates;
public:
    ProbSolv()
    {
        _Solve();
    }
    ~ProbSolv(){}
private:
    void _Solve(){
        vi viStates;
        FOR(s, NUM_HOUSES){
            int state;
            cin >> state;
            viStates.push_back(state);
        }
        m_vviDualStates.push_back(viStates);
        m_vviDualStates.push_back(viStates);
        int days;
        cin >> days;

        int states[NUM_HOUSES];
        FOR(i, NUM_HOUSES){
            states[i] = viStates[i];
        }

        vi viAns = cellCompete(states, days);
        
        for(auto ans : viAns){
            cout << ans << " ";
        }
        cout <<endl;
    }

    vector<int> cellCompete(int* states, int days){
        
        FOR(i, NUM_HOUSES){
            m_vviDualStates[0][i] = states[i];
        }

        FOR(d, days){
            const int i = d%2;
            const int ni = (d+1)%2;
            FOR(h, NUM_HOUSES){
                if(h == 0){
                    if(m_vviDualStates[i][h+1] == 0){
                        m_vviDualStates[ni][h] = 0;
                    }
                    else{
                        m_vviDualStates[ni][h] = 1;
                    }
                }
                else if(h == (NUM_HOUSES-1)){
                    if(m_vviDualStates[i][h-1] == 0){
                        m_vviDualStates[ni][h] = 0;
                    }
                    else{
                        m_vviDualStates[ni][h] = 1;
                    }
                }
                else{
                    if(m_vviDualStates[i][h-1] == m_vviDualStates[i][h+1]){
                        m_vviDualStates[ni][h] = 0;
                    }
                    else{
                        m_vviDualStates[ni][h] = 1;
                    }
                }
            }
        }
        const int resIdx = days%2;
        return m_vviDualStates[resIdx];
    }
};


int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int numTCs = 0;
    cin >> numTCs;
    FOR(tc, numTCs){
        cout << "#" << tc+1 <<" ";
        ProbSolv ps;
    }
    return 0;
}
