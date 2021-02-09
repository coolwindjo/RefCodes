#include "../../ProbSolvStart.h"

class ProbSolv
{
public:
    ProbSolv()
    {
        _Solve();
    }
    ~ProbSolv(){}
private:
    // Complete the sockMerchant function below.
    int sockMerchant(int n, vector<int> ar) {
        sort(ar.begin(), ar.end());
        int pCnt = 0;
        int f = ar[0];
        FOR_INC (i, 1, n) {
            if (ar[i] == f) {
                pCnt++;
                f = -1;
            }
            else {
                f = ar[i];
            }
        }
        return pCnt;
    }

    void _Solve(){
        // ofstream fout(getenv("OUTPUT_PATH"));

        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string ar_temp_temp;
        getline(cin, ar_temp_temp);

        const string delims{" "};
        vector<string> ar_temp = _SplitString(ar_temp_temp, delims);

        vector<int> ar(n);

        for (int i = 0; i < n; i++) {
            int ar_item = stoi(ar_temp[i]);

            ar[i] = ar_item;
        }

        int result = sockMerchant(n, ar);

        cout << result;
        // fout << result << "\n";

        // fout.close();
    }

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
    FOR(tc, numTCs){
        cout << "#" << tc+1 <<" ";
        ProbSolv ps;
        cout << endl;
    }
    return 0;
}
