#if 0
#define TEST
#endif // 1

#include "../../ProbSolvStart.h"

class ProbSolv
{
    vi m_viP;
    vi m_viS;
    vi m_viQ;
    int m_lastBig;
    int m_numPs;
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
        vstr vstrP = _SplitString(line, string("\r, []"));
        FOR(i, 10){
            std::getline(std::cin, line);
            if(line.length() > 2){
                break;
            }
        }
        vstr vstrS = _SplitString(line, string("\r, []"));

        for (auto strp : vstrP){
            int p = std::stoi(strp);
            m_viP.push_back(p);
        }
        for (auto strs : vstrS){
            int s = std::stoi(strs);
            m_viS.push_back(s);
        }

        _Solve();
    }
    ~ProbSolv(){}

    int Push(const int finDate){
        /*/
        if (m_lastBig < finDate)  m_lastBig = finDate;
        m_numPs++;
        return m_lastBig;
        /*/
        m_viQ.push_back(finDate);
        return m_viQ[0];
        //*/
    }
    int Flush(){
        /*/
        int numPs = m_numPs;
        m_numPs = 0;
        m_lastBig = 0;
        /*/
        int numPs = m_viQ.size();
        m_viQ.clear();
        //*/
        return numPs;
    }

private:
    void _Solve(){
        m_numPs = 0;
        m_lastBig = 0;
        vi viRel;
        int lastBiggest = 101;
        for(int i=0; i<m_viP.size(); ++i){
            const double p = m_viP[i];
            const double s = m_viS[i];
            const int finDate = (int)((99.0-p)/s +1.0); // 100.0 -> 99.0
            if (lastBiggest < finDate){
                viRel.push_back(Flush());
            }
            lastBiggest = Push(finDate);
        }
        viRel.push_back(Flush());
        for(auto rel:viRel){
            cout << rel << ", ";
        }
    } // _Solve()

    vstr _SplitString(string line, const string &delims) {
#ifdef TEST
        cout << "1) line: " << line <<endl;
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
            for(string name : vstrSplits) {
                cout << name << " ";
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
