#if 0
#define SPLIT_DEBUG
#endif // 1

#include "../../ProbSolvStart.h"

class ProbSolv
{
    vi m_viNums;
    vvi m_vviBiggerFirst;
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
        vstr vstrNums = _SplitString(line, string("\r, []"));
        for(auto str : vstrNums){
            m_viNums.push_back(std::stoi(str));
        }

        _Solve();
    }
    ~ProbSolv(){}

    int Digit(const int num){
        if (num < 10) return 1;
        return 1 + Digit(num/10);
    }

private:
    void _Solve(){
        std::sort(m_viNums.begin(), m_viNums.end(), [](const int a, const int b){
            return a>b;
        });
        int prevDigit = Digit(m_viNums[0]);
        vi viNums;
        for (int num : m_viNums){
            int digit = Digit(num);
            if (digit < prevDigit){
                m_vviBiggerFirst.push_back(viNums);
                viNums.clear();
                prevDigit = digit;
            }
            viNums.push_back(num);
        }
        m_vviBiggerFirst.push_back(viNums);
        string ans;
        
        cout << ans;
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
