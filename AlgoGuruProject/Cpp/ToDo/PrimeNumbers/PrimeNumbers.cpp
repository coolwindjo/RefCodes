#if 0
#define TEST
#endif // 1
#if 0
#define SPLIT_DEBUG
#endif // 1

#include "../../ProbSolvStart.h"

class ProbSolv
{
    string m_strNums;
    unordered_set<int> m_hash;
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
        vstr vstrNums = _SplitString(line, string("\r, []\""));
        m_strNums = vstrNums[0];

        _Solve();
    }
    ~ProbSolv(){}

    bool IsPrime(const int num){
        if ((num == 0) || (num == 1)) return false;
        if ((num == 2) || (num == 3) || (num == 5) || (num == 7)) return true;
        if (num%2 == 0) return false;
        bool isPrime = true;
        int n = (num>>1);
        for (int i=3;i<n;i+=2) {
            if (num%i == 0){
                isPrime = false;
                break;
            }
        }
        return isPrime;
    }

    void Swap(const int idxA, const int idxB){
        const int tmpB = m_strNums[idxA];
        m_strNums[idxA] = m_strNums[idxB];
        m_strNums[idxB] = tmpB;
    }

    void STL_Perm() {
        std::sort(m_strNums.begin(), m_strNums.end());
        do{
            string combined = "";
            for (auto num : m_strNums){ 
                combined += string({num}); // string strNum{num};
                const int combNum = std::stoi(combined);
                if (IsPrime(combNum)) {
                    m_hash.insert(combNum);
#ifdef TEST
                    cout << combNum << " ";
#endif
                }
            }
        } while(std::next_permutation(m_strNums.begin(), m_strNums.end()));
    }

    void DFS_Perm(const int begin, const int end){
        if (begin+1 == end) {
            string combined = "0";
            for (int i=0; i<m_strNums.size(); ++i){ 
                combined += string({m_strNums[i]});
                const int combNum = std::stoi(combined);
                if (IsPrime(combNum)) {
                    m_hash.insert(combNum);
#ifdef TEST
                    cout << combNum << " ";
#endif
                }
            }
            return;
        }

        for (int i=begin; i<end; ++i){
            Swap(begin, i);
            DFS_Perm(begin+1, end);
            Swap(begin, i);
        }
    }

private:
    void _Solve(){
        /*/
        STL_Perm();
        /*/
        // for (int i=0; i<m_viNums.size(); ++i) {
        //     DFS_Perm(i, m_viNums.size());
        // }
        DFS_Perm(0, m_strNums.size());
        //*/
        cout << m_hash.size();
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
