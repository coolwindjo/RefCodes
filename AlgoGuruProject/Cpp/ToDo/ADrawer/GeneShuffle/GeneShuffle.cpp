#include "../../ProbSolvStart.h"

typedef unordered_set<int> hsi;

const int MAX_N = 100000 + 1;
class ProbSolv{
    int m_N;
#if 0
    vstr m_vstrSegment;
#endif //0
    int m_arnGeneCodeA[MAX_N];
    int m_arnGeneCodeB[MAX_N];
public:
    explicit ProbSolv(const int N){
        m_N = N;
        FOR(i, m_N){
            cin >> m_arnGeneCodeA[i];
        }
        FOR(i, m_N){
            cin >> m_arnGeneCodeB[i];
        }
        Solve();
    }
    virtual ~ProbSolv(){}

#if 0
    int GetNumSegments(void){
        return static_cast<int>(m_vstrSegment.size());
    }

    std::string &GetSegment(const size_t idx=0){
        return m_vstrSegment.at(idx);
    }
#endif //0

    void Solve(void){
        hsi lnStoredCodes;
        hsi lnTargetCodes;
        int begin = 0;
        int isCut = 0;
        FOR(end, m_N){
            if(m_arnGeneCodeA[end] == m_arnGeneCodeB[end]){
                if (lnStoredCodes.empty()){
                    isCut = 1;
                }
            }
            else{
                lnStoredCodes.insert(m_arnGeneCodeA[end]);
                lnTargetCodes.insert(m_arnGeneCodeB[end]);
                if (CheckWithStoredCodes(lnTargetCodes, lnStoredCodes) == 1){
                    isCut = 1;
                }
            }

            if (isCut == 1){
#if 0
                std::stringstream ssout;
                ssout << begin+1;
                std::string strGenSeg = ssout.str();
#else
                std::string strGenSeg = std::to_string(begin + 1);
#endif //0
                strGenSeg += "-";
                strGenSeg += std::to_string(end + 1);
                cout << strGenSeg << " ";
#if 0
                m_vstrSegment.push_back(strGenSeg);
#endif
                begin = end + 1;
                isCut = 0;
            }
        }
    }

    int CheckWithStoredCodes(hsi &lnTargetCodesOut, hsi &lnStoredCodesOut){
        int found = 0;
        hsi::iterator itT=lnTargetCodesOut.begin();
        while (itT!=lnTargetCodesOut.end()){
            hsi::iterator itS = lnStoredCodesOut.find(*itT);
            if(itS != lnStoredCodesOut.end()){
                itT = lnTargetCodesOut.erase(itT);
                lnStoredCodesOut.erase(itS);
                if (lnStoredCodesOut.empty()){
                    found = 1;
                    return found;
                }
            }
            else{
                itT++;
            }
        }
        if (lnStoredCodesOut.empty()){
            found = 1;
        }
       return found;
    }
    
#if 0
    const int Factor(const int n, const int depth){
        if (depth == 1) {
            return n;
        }
        else if (depth == 0) {
            return 1;
        }
        else{
            if (n <= 1){
                return n;
            }
            else{
                return n*Factor(n-1, depth-1);
            }
        }
    }

    
    int FindInPermList(const std::string &strGeneCode, const int begin, const int end, const int depth, int (&arnCode)[MAX_N]){
        int found = 0;
        if (depth == (end-begin+1)){
            std::string strCode;
            FOR_INC(i, begin, end+1){
                strCode += std::to_string(arnCode[i]);
            }
            if (strGeneCode.compare(strCode) == 0){
                found = 1;
                return found;
            }
        }
        else{
            FOR_INC(i, begin+depth, end+1){
                Swap(begin+depth, i, arnCode);
                found = FindInPermList(strGeneCode, begin, end, depth+1, arnCode);
                Swap(begin+depth, i, arnCode);
                if (found == 1){
                    return found;
                }
            }
        }
        return found;
    }
    
    void Swap(const int i, const int j, int (&arnCode)[MAX_N]){
        int tmp = arnCode[i];
        arnCode[i] = arnCode[j];
        arnCode[j] = tmp;
    }
#endif

};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int numTCs = 0;
    int N = 0;
    cin >> numTCs;
    P_IFNOT(numTCs>0, numTCs);

    FOR(i, numTCs){
        cin >> N;
        P_IFNOT(N>0, N);
        ProbSolv ps(N);
#if 0
        const int numSegments = ps.GetNumSegments();
        FOR(i, numSegments){
            cout << ps.GetSegment(i) << " ";
        }
#endif
        cout << endl;
    }

    return 0;
}
