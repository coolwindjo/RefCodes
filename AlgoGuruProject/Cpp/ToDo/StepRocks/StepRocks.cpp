#if 0
#define SPLIT_DEBUG
#endif // 1

#include "../../ProbSolvStart.h"

typedef pair<ii, int> ii_i;
typedef vector<ii_i> vii_i;

constexpr int EPS = 1;
class ProbSolv
{
    int m_dist;
    int m_n;
    vi m_viRocks;
public:
    ProbSolv()
    {
        cin >> m_dist;

        string line;
        FOR(i, 10){
            std::getline(std::cin, line);
            if(line.length() > 2){
                break;
            }
        }
        vstr vstrRocks = _SplitString(line, string("\r\t, []"));
        for (auto str : vstrRocks) {
            m_viRocks.push_back(std::stoi(str));
        }

        cin >> m_n;

        _Solve();
        // _Solve_JoSH();
    }
    ~ProbSolv(){}

    bool IsTooBig(const int mid) {
        int rmCnt = 0;
        int prev = 0;
        for (auto rock : m_viRocks) {
            if ((rock-prev) < mid) {
                if ((++rmCnt) > m_n) break;
            }
            else {
                prev = rock;
            }
        }
        return (rmCnt > m_n);
    }
private:
    void _Solve() {
        int answer = 0;
        m_viRocks.push_back(m_dist);
        std::sort(m_viRocks.begin(), m_viRocks.end());

        int lo = 1;
        int hi = m_dist;
        while ((hi-lo) > EPS){
            int mid = (lo + hi) >> 1;
            if (IsTooBig(mid)) {
                hi = mid;
            }
            else {
                lo = mid;
                answer = lo;
            }
        }
        std::cout << answer;
    }

    void _Solve_JoSH(){
        std::sort(m_viRocks.begin(), m_viRocks.end());
        vii_i vii_iInter;
        int prev = 0;
        for (int i=1; i<m_viRocks.size(); ++i) {
            int first = m_viRocks[i-1];
            int second = m_viRocks[i];
            vii_iInter.push_back(ii_i(ii(first - prev, second - prev), first));
            prev = first;
        }
        int last = m_viRocks.back();
        vii_iInter.push_back(ii_i(ii(last - prev, m_dist - prev), last));

        std::sort(vii_iInter.begin(), vii_iInter.end(), [](const ii_i &a, const ii_i &b){
            if (a.first.first==b.first.first){
                return a.first.second < b.first.second;
            }
            return a.first.first < b.first.first;
        });
        vi viRem;
        for (int i=m_n; i<vii_iInter.size(); ++i){
            viRem.push_back(vii_iInter[i].second);
        }
        std::sort(viRem.begin(), viRem.end());

        vi viAns;
        prev = 0;
        for (auto r : viRem) {
            viAns.push_back(r-prev);
            prev = r;
        }
        viAns.push_back(m_dist-prev);
        std::sort(viAns.begin(), viAns.end());
        cout << viAns[0];
        
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
