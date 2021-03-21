#if 0
#define TEST
#endif // 1

#if 0
#define USE_IDX_MAP
#endif // 1

#include "../../ProbSolvStart.h"

class ProbSolv
{
    vstr vstrGenre;
    vi viPlays;
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
        const string delims{"\", []\r"};
        vstrGenre = _SplitString(line, delims);

        FOR(i, 10){
            std::getline(std::cin, line);
            if(line.length() > 2){
                break;
            }
        }
        vstr vstrPlays = _SplitString(line, delims);
        for (auto strPlays : vstrPlays) {
            viPlays.push_back(std::stoi(strPlays));
        }

        _Solve();
    }
    ~ProbSolv(){}
private:
    void _Solve(){
        
    }
    void _Solve_arch(){
        typedef std::pair<int, vii> i_vii;
        typedef std::vector<i_vii> vivii;
        vivii viviiTotVecPlaysId;

#ifdef USE_IDX_MAP
        typedef std::unordered_map<string, int> hash_str_i;
        hash_str_i hash_striGenreIdx;
#else
        typedef std::pair<string, i_vii> str_ivii;
#if 0   // only key can be compared... the code below is not possible
        struct cmp {
            bool operator()(const str_ivii &a, const str_ivii &b) const {
                return a.second.first > b.second.first;
            }
        };
        typedef std::map<string, i_vii, cmp> hash_str_ivii;
#else
        typedef std::unordered_map<string, i_vii> hash_str_ivii;
#endif
        hash_str_ivii hash_striviiGenre;
#endif // USE_IDX_MAP
        int genreCnt = 0;
        FOR(i, vstrGenre.size()){
            string genre = vstrGenre[i];
            int plays = viPlays[i];
#ifdef USE_IDX_MAP
            hash_str_i::iterator it = hash_striGenreIdx.find(genre);
            if (it == hash_striGenreIdx.end()) {
                vii viiTotVecPlaysId;
                viiTotVecPlaysId.push_back(ii(plays, i));
                viviiTotVecPlaysId.push_back(i_vii(plays, viiTotVecPlaysId));
                hash_striGenreIdx.insert(str_i(genre, genreCnt++));
            }
            else {
                // vivii[hash->int].vii.push_back()
                viviiTotVecPlaysId[it->second].second.push_back(ii(plays, i));
                // vivii[hash->int].int+=plays
                viviiTotVecPlaysId[it->second].first+=plays;
            }
#else
            hash_str_ivii::iterator it = hash_striviiGenre.find(genre);
            if (it == hash_striviiGenre.end()) {
                vii viiTotVecPlaysId;
                viiTotVecPlaysId.push_back(ii(plays, i));
                hash_striviiGenre.insert(str_ivii(genre, i_vii(plays, viiTotVecPlaysId)));
            }
            else {
                // hash->ivii.vii.push_back()
                it->second.second.push_back(ii(plays, i));
                // hash->ivii.int
                it->second.first+=plays;
            }
#endif // USE_IDX_MAP
        }

#ifndef USE_IDX_MAP
        hash_str_ivii::iterator it = hash_striviiGenre.begin();
        for (; it!=hash_striviiGenre.end(); ++it) {
            viviiTotVecPlaysId.push_back(
                // hash->ivii.int, hash->ivii.vii
                i_vii(it->second.first, it->second.second));
        }
#endif // USE_IDX_MAP

#if 0 // Impossible to sort a map
        std::sort(hash_striviiGenre.begin(), hash_striviiGenre.end(),
        [](const string &a, const string &b){
            return a.length() > b.length();
        });
#else
        std::sort(viviiTotVecPlaysId.begin(), viviiTotVecPlaysId.end(),
        [](const i_vii &a, const i_vii &b){
            return a.first > b.first;
        });
#endif
        vi viPick;
        for (auto i_viiTotVecPlaysId : viviiTotVecPlaysId) {
            auto viiPlaysId = i_viiTotVecPlaysId.second;
            std::sort(viiPlaysId.begin(), viiPlaysId.end(),
            [](const ii &a, const ii &b){
                if (a.first == b.second) {
                    return a.second < b.second;
                }
                return a.first > b.first;
            });
            for (int j=0; (j<2) && (j<viiPlaysId.size()); ++j) {
                viPick.push_back(viiPlaysId[j].second);
            }
        }
        for (auto id : viPick) {
            cout << id << " ";
        }
    } // Solve

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
