#if 1
#define TEST
#endif // 1

#include "../../ProbSolvStart.h"

typedef enum {
    eU=-1, eD=1,
    eDIR_LEN
} Dir_e;

class ProbSolv
{
public:
    ProbSolv()
    {
        _Solve();
    }
    ~ProbSolv(){}
private:

    int countingValleys(int steps, string path) {
        vector<int> viPath;
        for (int i=0; i<steps; i++){
            if (path[i] == 'U') {
                viPath.push_back(-1);
            }
            else if (path[i] == 'D') {
                viPath.push_back(1);
            }
            else{}
        }
        int level = 0;
        int vCnt = 0;
        for (int i=0; i<steps; i++) {
            level += viPath[i];
            if (level == 0) {
                if (viPath[i] < 0) {
                    vCnt++;
                }
                else {}
            }
        }
        return vCnt;
    }

    string ltrim(const string &str) {
        string s(str);

        s.erase(
            s.begin(),
            find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
        );

        return s;
    }

    string rtrim(const string &str) {
        string s(str);

        s.erase(
            find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
            s.end()
        );

        return s;
    }

    void _Solve(){
        // ofstream fout(getenv("OUTPUT_PATH"));

        string steps_temp;
        while(steps_temp.length() == 0){
            std::getline(std::cin, steps_temp);    // removing \n
        }

        int steps = stoi(ltrim(rtrim(steps_temp)));

        string path;
        getline(cin, path);

        int result = countingValleys(steps, path);

        cout << result;
        // fout << result << "\n";

        // fout.close();
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
