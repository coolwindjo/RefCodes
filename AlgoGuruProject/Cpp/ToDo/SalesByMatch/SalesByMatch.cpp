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

    vector<string> split_string(string input_string) {
        string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
            return x == y and x == ' ';
        });

        input_string.erase(new_end, input_string.end());

        while (input_string[input_string.length() - 1] == ' ') {
            input_string.pop_back();
        }

        vector<string> splits;
        char delimiter = ' ';

        size_t i = 0;
        size_t pos = input_string.find(delimiter);

        while (pos != string::npos) {
            splits.push_back(input_string.substr(i, pos - i));

            i = pos + 1;
            pos = input_string.find(delimiter, i);
        }

        splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

        return splits;
    }

    void _Solve(){
        // ofstream fout(getenv("OUTPUT_PATH"));

        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string ar_temp_temp;
        getline(cin, ar_temp_temp);

        vector<string> ar_temp = split_string(ar_temp_temp);

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
