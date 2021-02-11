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
    vstr vstrPlays;
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
        vstrGenre = _SplitString(line, delims);

        FOR(i, 10){
            std::getline(std::cin, line);
            if(line.length() > 2){
                break;
            }
        }
        vstrPlays = _SplitString(line, delims);

        _Solve();
    }
    ~ProbSolv(){}
private:
    void _Solve(){
        typedef std::unordered_map<int, int> mapii;
        typedef std::pair<int, mapii> i_mapii;

#ifdef USE_IDX_MAP
        typedef vector<i_mapii> vi_mapii;
        vi_mapii vi_mapiiTotPlaysSongNum;
        typedef std::unordered_map<string, int> hash_str_i;
        hash_str_i hashGenreWithPlaysIdx;
#else
        typedef std::pair<string, i_mapii> str_imapii;
#if 0   // only key can be compared... the code below is not possible
        struct cmp {
            bool operator()(const str_imapii &a, const str_imapii &b) const {
                return a.second.first > b.second.first;
            }
        };
        typedef std::map<string, i_mapii, cmp> hash_str_imapii;
#else
        typedef std::map<string, i_mapii> hash_str_imapii;
#endif
        hash_str_imapii hashGenreWithPlays;
#endif

        FOR(i, vstrGenre.size()){
            string genre = vstrGenre[i];
            int plays = std::stoi(vstrPlays[i]);
#ifdef USE_IDX_MAP
            hash_str_i::iterator pit = hashGenreWithPlaysIdx.find(genre);
            if (pit == hashGenreWithPlaysIdx.end()) {  // new genre
                mapii mapiiPlaysSongNum;
                mapiiPlaysSongNum.insert(ii(plays, i));
                vi_mapiiTotPlaysSongNum.push_back(i_mapii(plays, mapiiPlaysSongNum));
                hashGenreWithPlaysIdx.insert(str_i(genre, (vi_mapiiTotPlaysSongNum.size()-1)));
            }
            else {
                vi_mapiiTotPlaysSongNum[pit->second].first += plays;
                vi_mapiiTotPlaysSongNum[pit->second].second.insert(ii(plays, i));
            }
#else
            hash_str_imapii::iterator it = hashGenreWithPlays.find(genre);
            if (it == hashGenreWithPlays.end()) {  // new genre
                mapii mapiiPlaysSongNum;
                mapiiPlaysSongNum.insert(ii(plays, i));
                hashGenreWithPlays.insert(str_imapii(genre, i_mapii(plays, mapiiPlaysSongNum)));
            }
            else {
                it->second.first += plays;
                it->second.second.insert(ii(plays, i));
            }
#endif 
        }

#ifndef USE_IDX_MAP
        typedef vector<i_mapii> vi_mapii;
        vi_mapii vi_mapiiTotPlaysSongNum;
        for (hash_str_imapii::iterator itGenre=hashGenreWithPlays.begin();
        itGenre!=hashGenreWithPlays.end(); ++itGenre) {
            vi_mapiiTotPlaysSongNum.push_back(itGenre->second);
        }
#endif

#if 1 // Impossibleto sort unordered map
        std::sort(vi_mapiiTotPlaysSongNum.begin(), vi_mapiiTotPlaysSongNum.end(),
        [](const i_mapii &a, const i_mapii &b){
            return a.first > b.first;
        });
#else
        std::sort(hashGenreWithPlaysIdx.begin(), hashGenreWithPlaysIdx.end(),
        [](const str_i &a, const str_i &b){
            return a.second > b.second;
        });
#endif
        vi viCollection;
        for (i_mapii i_mapiiGenre : vi_mapiiTotPlaysSongNum) {
            vii viiPlaysSongNum;
            mapii::iterator itPlays = i_mapiiGenre.second.begin();
            for (; (itPlays!=i_mapiiGenre.second.end()); ++itPlays) {
                viiPlaysSongNum.push_back(*itPlays);
            }
            std::sort(viiPlaysSongNum.begin(), viiPlaysSongNum.end(),
            [](const ii &a, const ii &b){
                if (a.first == b.first) {
                    return a.second < b.second;
                }
                return a.first > b.first;
            });
            for (int i=0; i<2; ++i){
                viCollection.push_back(viiPlaysSongNum[i].second);
            }
        }

        for (auto ans : viCollection) {
            cout << ans << " ";
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
