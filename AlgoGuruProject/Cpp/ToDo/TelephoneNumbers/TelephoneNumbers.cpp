#if 0
#define TEST
#endif // 1

#include "../../ProbSolvStart.h"

class ProbSolv
{
    vstr vstrPhoneBook;
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
        const string delims{"\", []"};
        vstrPhoneBook = _SplitString(line, delims);

        _Solve();
    }
    ~ProbSolv(){}
private:
    void _Solve(){
        sort(vstrPhoneBook.begin(), vstrPhoneBook.end());

        bool isPrefix = false;
        string strPrev = "INVALID";
        for (string number : vstrPhoneBook) {
            if (strPrev == number.substr(0, strPrev.length()))
            {
                isPrefix = true;
                break;
            }
            strPrev = number;
        }
        if (!isPrefix) cout << "false";
        else cout << "true";
    }

    void _SolveUsingSet(){ // faster than the one using sort
        std::set<string> hsh;
        bool isPrefix = false;
        for (string number : vstrPhoneBook){
            hsh.insert(number);
            if (hsh.size() < 2) {
                continue;
            }
            std::set<string>::iterator prevIt = hsh.lower_bound(number);
            std::set<string>::iterator nextIt = hsh.upper_bound(number);
            if (prevIt != hsh.begin()) {
                string prevNum;
                if ((prevNum = *(--prevIt)) != "") {
                    if (prevNum == number.substr(0, prevNum.length())) {
                        isPrefix = true;
                        break;
                    }
                }
            }

            if (nextIt != hsh.end()) {
                string nextNum;
                if ((nextNum = *nextIt) != "") {
                    if (number == nextNum.substr(0, number.length())) {
                        isPrefix = true;
                        break;
                    }
                }
            }
        }
        
        if (isPrefix) cout << "false";
        else cout << "true";

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
