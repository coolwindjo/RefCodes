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

        int numFeatures = 0;
        int topFeatures = 0;
        vstr possibleFeatures;
        int numFeatureRequests = 0;
        vstr featureRequests;

        cin >> numFeatures >> topFeatures;
        FOR(i, numFeatures){
            string possFeat;
            cin >> possFeat;
            possibleFeatures.push_back(possFeat);
        }
        cin >> numFeatureRequests;
        FOR(i, numFeatureRequests){
            char szFeRe[256];
            cin.getline(szFeRe, 256);
            string strFeRe(szFeRe);
            if(strFeRe.length() == 0){
                i--;
                continue;
            }
            featureRequests.push_back(strFeRe);
        }
        vstr vstrAns = popularNFeatures(numFeatures, topFeatures, possibleFeatures, numFeatureRequests, featureRequests);
        for(auto ans : vstrAns){
            cout << ans << " ";
        }
        
    }

    vector<string> popularNFeatures(int numFeatures, int topFeatures, 
                                vector<string> possibleFeatures, 
                                int numFeatureRequests,
                                vector<string> featureRequests)
    {
        // WRITE YOUR CODE HERE
        // vi viVote;
        vi_str vote_string;
        FOR(i, numFeatures){
            vote_string.push_back(i_str(0, possibleFeatures[i]));
        }
        for(auto featReq : featureRequests){
            vstr tokens;
            stringstream check(featReq);
            string strCandidate;
            while(getline(check, strCandidate, ' ')){
                int idx = 0;
                if((idx = strCandidate.rfind(',')) > 0){
                    strCandidate = strCandidate.substr(0,idx);
                }
                
                tokens.push_back(strCandidate);
            }

            for(auto tok : tokens){
                FOR(j, numFeatures)
                if(possibleFeatures[j].compare(tok) == 0)
                {
                    vote_string[j].first++;
                }
            }
        }

        sort(vote_string.begin(), vote_string.end());

        vstr vstrAns;
        FOR_DEC(i, numFeatures-topFeatures, numFeatures){
            vstrAns.push_back(vote_string[i].second);
        }

        return vstrAns;
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
