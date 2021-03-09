#if 0
#define TEST
#endif // 1

#include "../../ProbSolvStart.h"

class ProbSolv
{
    vector<vstr> vvstrClothes;
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
        const string delims{"\", []"};
        vstr vstrClothes = _SplitString(line, delims);
        bool isFirst = true;
        for (int i=0; i<vstrClothes.size(); i+=2) {
            vstr vstrCombi;
            string cloth1 = vstrClothes[i];
            string cloth2 = vstrClothes[i+1];
            vstrCombi.push_back(cloth1);
            vstrCombi.push_back(cloth2);
            vvstrClothes.push_back(vstrCombi);
        }

        _Solve();
    }
    ~ProbSolv(){}

    void DFS(  const vi &viNumItems, const int beginIdx, const int prevProductVal,
                int &sumNumCombies) {
        W_IFNOT(beginIdx <= viNumItems.size());

        if (beginIdx == viNumItems.size()) {
            return;
        }

        int productVal = prevProductVal * viNumItems[beginIdx];
        sumNumCombies += productVal;

        FOR_INC(nextIdx, beginIdx+1, viNumItems.size()){
            DFS(viNumItems, nextIdx, productVal, sumNumCombies);
        }
    }

private:
    void _Solve() {
        typedef std::unordered_map<string, int> map_str_i;
        map_str_i map;
        for (vstr vstrCombi : vvstrClothes) {
            map[vstrCombi[1]]++;
        }

        // arithResult = (C1+1)(C2+1)(C3+1)...(Cn+1) - 1
        int arithResult = 1;
        for (map_str_i::iterator it=map.begin(); it!=map.end(); ++it) {
            arithResult *= (it->second + 1);
        }
        arithResult -= 1;

        cout << arithResult;
    }

    void _SolveAllowingDuplicates(){
        typedef std::unordered_set<string> setstr;
        typedef std::pair<string, setstr> str_setstr;
        typedef std::unordered_map<string, setstr> map_str_setstr;
        map_str_setstr map;
        for (vstr vstrCombi : vvstrClothes) {
            map_str_setstr::iterator it;
            if ((it = map.find(vstrCombi[1])) == map.end()){ // new kind
                setstr setCloth;
                setCloth.insert(vstrCombi[0]);
                map.insert(str_setstr(vstrCombi[1], setCloth));
            }
            else {
                it->second.insert(vstrCombi[0]);
            }
        }

        vi viNumItems;
        map_str_setstr::iterator it;
        for (it=map.begin(); it!=map.end(); ++it) {
            viNumItems.push_back(it->second.size());
        }
        int sumNumCombies = 0;
        FOR(i, viNumItems.size()){
            DFS(viNumItems, i, 1, sumNumCombies);
        }

        cout << sumNumCombies;
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
