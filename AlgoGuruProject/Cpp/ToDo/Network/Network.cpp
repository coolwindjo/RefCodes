#if 0
#define SPLIT_DEBUG
#endif // 1

#include "../../ProbSolvStart.h"

class ProbSolv
{
    int m_n;
    vvi m_vviConnects;
    vi  m_viVisit;
    int m_rem;
public:
    ProbSolv()
    {
        cin >> m_n;

        string line;
        FOR(i, 10){
            std::getline(std::cin, line);
            if(line.length() > 2){
                break;
            }
        }

        vstr vstrCons = _SplitString(line, string("\r,\t []"));
        FOR(i, m_n){
            vi viCons;
            FOR(j, m_n){
                viCons.push_back(std::stoi(vstrCons[i*m_n+j]));
            }
            m_vviConnects.push_back(viCons);
        }

        _Solve();
    }
    ~ProbSolv(){}

    bool Visited(const int com){
        return m_viVisit[com] > 0;
    }
    void DFS(const int com, const int cnt){
        m_viVisit[com] = cnt;
        if (--m_rem == 0) {
            return;
        }
        FOR(i, m_n){
            if (m_vviConnects[com][i] == 1) {
                if (Visited(i)) continue;
                DFS(i, cnt);
            }
        }
    }

private:
    void _Solve(){
        FOR(i, m_n){
            m_viVisit.push_back(0);
        }
        m_rem = m_n;
        int cnt = 1;
        FOR(i, m_n){
            if (Visited(i)) continue;
            DFS(i, cnt++);
            if (m_rem == 0) break;
        }
        int numNets = 0;
        for(auto num : m_viVisit){
            numNets = std::max(num, numNets);
        }
        cout << numNets;
    } // _Solve()

    vstr _SplitString(string line, const string &delims) {
#ifdef SPLIT_DEBUG
        cout << "\n1) line: " << line <<endl;
#endif
        string::iterator newEnd = unique(line.begin(), line.end(), [] (const char &x, const char &y) {
            return x==y and x==' ';
        });
#ifdef SPLIT_DEBUG
        cout << "2) line: " << line <<endl;
#endif

        line.erase(newEnd, line.end());
#ifdef SPLIT_DEBUG
        cout << "3) line: " << line <<endl;
#endif

        while (line[line.length() - 1] == ' ') {
            line.pop_back();
        }
#ifdef SPLIT_DEBUG
        cout << "4) line: " << line <<endl;
#endif

        vstr vstrSplits;

        size_t prev = 0;
        size_t pos;
        while ((pos = line.find_first_of(delims, prev)) != string::npos) {
            if (pos > prev) {
                vstrSplits.push_back(line.substr(prev, pos-prev));
            }
#ifdef SPLIT_DEBUG
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
