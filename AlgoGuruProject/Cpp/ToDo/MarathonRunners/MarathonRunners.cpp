#if 0
#define TEST
#endif // 1

#include "../../ProbSolvStart.h"

class ProbSolv
{
    vstr vstrPartList;
    vstr vstrCompList;
public:
    ProbSolv()
    {
        string line;
        FOR(i, 10){
            std::getline(std::cin, line);
            if(line.length() >= 2){
                break;
            }
        }

        const string delimiters{", []\r\n"};
        vstrPartList = _SplitString(line, delimiters);

#ifdef TEST
        cout << "Participations: ";
        for(string name : vstrPartList) {
            cout << name << " ";
        }
        cout <<endl;
#endif

        FOR(i, 10){
            std::getline(std::cin, line);
            if(line.length() != 0){
                break;
            }
        }
        vstrCompList = _SplitString(line, delimiters);

#ifdef TEST
        cout << "Completions: ";
        for(string name : vstrCompList) {
            cout << name << " ";
        }
        cout <<endl;
#endif

        _Solve();
    }
    ~ProbSolv(){}
private:
    void _Solve(){
        std::map<string, int> hsh;
        for (string name : vstrPartList) {
            std::map<string, int>::iterator it = hsh.find(name);
            if (it != hsh.end()) {
                it->second++;
            }
            else {
                hsh.insert(std::pair<string, int>(name, 1));
            }
        }

        for (string name : vstrCompList) {
            std::map<string, int>::iterator it = hsh.find(name);
            W_IFNOT(it != hsh.end());
            if (it->second > 1) {
                it->second--;
            }
            else {
                hsh.erase(it);
            }
        }
        if (!hsh.empty()){
            cout << hsh.begin()->first;
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
