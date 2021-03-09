#if 0
#define TEST
#endif // 1

#include "../../ProbSolvStart.h"

class ProbSolv
{
    vi m_viP;
    int m_limit;
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
        cin >> m_limit;
        vstr vstrP = _SplitString(line, string("\r, []"));
        for(auto strP : vstrP){
            const int p = std::stoi(strP);
            m_viP.push_back(p);
        }

        _Solve();
    }
    ~ProbSolv(){}

private:
    void _Solve(){
        std::sort(m_viP.begin(), m_viP.end());
        int cnt = 0;
        int inBoat = -1;
        int lastIdx = m_viP.size()-1;
        for (int i=0; i<m_viP.size(); ++i){
            int p = m_viP[i];
            W_IFNOT(p < m_limit);

            if (p < 0) continue;

            int sum = inBoat + p;
            if ((inBoat < 0) || (sum > m_limit)) {
                inBoat = p;
                m_viP[i] = -1;
                if (sum > m_limit) cnt++;
                continue;
            }

            for (int j=lastIdx; j>=i; --j){
                sum = inBoat + m_viP[j];
                if (sum <= m_limit){
                    if (i==j) {
                        inBoat = -1;
                    }
                    else {
                        inBoat = p;
                    }
                    m_viP[j] = -1;
                    break;
                }
            }

            cnt++;
        }

        if (inBoat > 0){
            cnt++;
        }
        cout << cnt;
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
