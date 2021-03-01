#if 0
#define TEST
#endif // 1

#include "../../ProbSolvStart.h"

class ProbSolv
{
    int n;
    vi viTimes;
public:
    ProbSolv()
    {
        cin >> n;
        string line;
        FOR(i, 10){
            std::getline(std::cin, line);
            if(line.length() >= 2){
                break;
            }
        }
        const string delims{", []\r"};
        vstr vstrTimes = _SplitString(line, delims);
        for (auto t:vstrTimes){
            viTimes.push_back(std::stoi(t));
        }

        _Solve();
    }
    ~ProbSolv(){}
private:
    bool _IsEnough(const ll elapsed){
        ll sum = 0;
        for (int t : viTimes){
            sum += static_cast<ll>(elapsed/t);
        }
        return (sum >= n);
    }
    void _Solve(){
        ll answer = 0;
        std::sort(viTimes.begin(), viTimes.end());
        ll max = viTimes[0] * static_cast<ll>(n);   // ll*int = int
        ll min = viTimes[0];
        while (min<=max){
            ll mid = static_cast<ll>((min+max)*0.5);
            if (_IsEnough(mid)){
                answer = mid;
                max = mid-1; 
            }
            else{
                min = mid+1;
            }
        }
        cout << answer;
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
