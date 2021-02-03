#include "../../ProbSolvStart.h"

class ProbSolv
{
public:
    ProbSolv()
    {
        _Solve();
    }
    ~ProbSolv(){}
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
        vistr vistr_vote_string;
        for(auto posFeat : possibleFeatures){
            vistr_vote_string.push_back(i_str(0, posFeat));
        }

        for(auto featReq : featureRequests){
            vstr tokens;
            stringstream lineStream(featReq);
            string token;
            while(getline(lineStream, token, ' ')){
                int idx = 0;
                if((idx = token.rfind(',')) > 0){
                    token = token.substr(0,idx);
                }
                
                tokens.push_back(token);
            }

            for(auto tok : tokens){
                FOR(j, numFeatures)
                if(possibleFeatures[j].compare(tok) == 0)
                {
                    vistr_vote_string[j].first--;
                }
            }
        }

        sort(vistr_vote_string.begin(), vistr_vote_string.end());

        int numAns = topFeatures;
        vstr vstrAns;
        for(auto vote_string : vistr_vote_string){
            vstrAns.push_back(vote_string.second);
            if (--numAns == 0) break;
        }

        return vstrAns;
    }

};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int numTCs = 0;
    cin >> numTCs;
    FOR(tc, numTCs){
        cout << "#" << tc+1 <<" ";
        ProbSolv ps;
        cout << endl;
    }
    return 0;
}
