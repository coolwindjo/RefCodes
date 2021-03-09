#if 0
#define TEST
#endif // 1

#include "../../ProbSolvStart.h"

class ProbSolv
{
    vvi m_vviT;
public:
    ProbSolv()
    {
        string line;
        FOR(i, 10){
            std::getline(std::cin, line);
            if(line.length() > 2){
                break;
            }
        }
        vstr vstrT = _SplitString(line, string(", \r[]"));
        vi viRow;
        int rowCnt = 1;
        int cntAcc = rowCnt;
        for (int i=0; i<vstrT.size(); ++i){
            if (cntAcc == i) {
                m_vviT.push_back(viRow);
                viRow.clear();
                rowCnt++;
                cntAcc += rowCnt;
            }
            viRow.push_back(std::stoi(vstrT[i]));
        }
        m_vviT.push_back(viRow);

        _Solve();
    }
    ~ProbSolv(){}

    int DP(){
        int maxSum = 0;
        vi viPrevRow = m_vviT[m_vviT.size()-1];
        vi viRow;
        for (int i=m_vviT.size()-2; i>=0; --i){
            viRow = m_vviT[i];
            for (int j=0; j<viRow.size(); ++j){
                int val = viRow[j];
                int bigger = std::max(viPrevRow[j], viPrevRow[j+1]);
                viRow[j] = val + bigger;
            }
            viPrevRow.clear();
            viPrevRow = viRow;
        }
        maxSum = viRow[0];
        return maxSum;
    }

private:
    void _Solve(){
        int maxSum = DP();
        cout << maxSum;
    } // _Solve()

    vstr _SplitString(string line, const string &delims) {
#ifdef TEST
        cout << "\n1) line: " << line <<endl;
#endif
        string::iterator newEnd = unique(line.begin(), line.end(), [] (const char &x, const char &y) {
            return x==y and x==' ';
        });
#ifdef TEST
        cout << "2) line: " << line <<endl;
#endif

        line.erase(newEnd, line.end());
#ifdef TEST
        cout << "3) line: " << line <<endl;
#endif

        while (line[line.length() - 1] == ' ') {
            line.pop_back();
        }
#ifdef TEST
        cout << "4) line: " << line <<endl;
#endif

        vstr vstrSplits;

        size_t prev = 0;
        size_t pos;
        while ((pos = line.find_first_of(delims, prev)) != string::npos) {
            if (pos > prev) {
                vstrSplits.push_back(line.substr(prev, pos-prev));
            }
#ifdef TEST
            for(string str : vstrSplits) {
                cout << str << " ";
            }
            cout <<endl;
#endif
            prev = pos + 1;
        }

        if (prev < line.length()) {
            vstrSplits.push_back(line.substr(prev, min(pos, line.length()) - prev + 1));
        }

        return vstrSplits;
    }

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
