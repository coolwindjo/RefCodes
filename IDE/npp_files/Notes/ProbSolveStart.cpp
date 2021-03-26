#if 1
#define TEST
#endif // 1

#include <bits/stdc++.h>
using namespace std;

#if 1 // 61dd
class CoolTimer {
public:
    CoolTimer()
        : m_fn_name(nullptr)
        , m_fn_name_size(0)
    {
    }
    ~CoolTimer() {
        if (m_fn_name != nullptr) {
            delete[] m_fn_name;
            m_fn_name = nullptr;
        }
    }

    void On(const char* str) {
        // Get the name of the function.
        m_fn_name_size = strlen(str) + 1;
        if (m_fn_name == nullptr) {
            m_fn_name = new char[m_fn_name_size];
        }
        memcpy(m_fn_name, str, sizeof(char)*m_fn_name_size);

        // Start.
        _QueryPerformanceCounter(&m_begin);
    }

    void Off() {	
        // End.
        _QueryPerformanceCounter(&m_end);

        // Calculate the time.
        long seconds = m_end.tv_sec - m_begin.tv_sec;
        long nanoseconds = m_end.tv_nsec - m_begin.tv_nsec;
        double elapsed = seconds + nanoseconds*1e-9;

        // Print the message.
        ostringstream os;
        os << m_fn_name << "() takes [" << elapsed << "] seconds.\n"; 
        cout << os.str();
        if (m_fn_name != nullptr) {
            delete[] m_fn_name;
            m_fn_name = nullptr;
        }
    }
private:
    bool _QueryPerformanceCounter(timespec* performance_count) {
        /* Sanity check. */
        assert(performance_count != nullptr);
        /* Grab the current time. */
        clock_gettime(CLOCK_REALTIME, performance_count);
        return true;
    }

    timespec m_begin;
    timespec m_end;
    char* m_fn_name;
    size_t m_fn_name_size;
} Timer;
#endif

#pragma GCC optimize("O2") 
#define FOR_INC(i, from, to) for(int (i)=(from); (i)<(to); ++(i))
#define FOR_DEC(i, from, to) for(int (i)=(to)-1; (i)>=(from); --(i))
#define FOR(i, to) FOR_INC((i), 0, (to))
#define OOR(x, min, max) (((x) < (min) || (x) > (max)))

static const int WarnIfNot(const int condFlag, const char* condition){
 	if (condFlag == 0) {
        cout << "Warning: [" << condition << "] is violated!\n";
    }
    return condFlag;
}
#define W_IFNOT(cond) WarnIfNot((cond), (#cond))
#define P_IFNOT(cond, var) if (!W_IFNOT(cond)) cout << "= " << var <<endl;

typedef long long ll;
constexpr int INF = 987654321;

typedef vector<string> vstr;
typedef vector<vstr> vvstr;
typedef pair<int, string> i_str;
typedef vector<i_str> vistr;
typedef pair<string, int> str_i;
typedef vector<str_i> vstri;
typedef vector<char> vc;
typedef vector<vc> vvc;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef pair<int, ii> i_ii;
typedef queue<ii> qii;
typedef queue<int> qi;
typedef priority_queue<i_ii> pqi_ii;    // for Dijkstra

#if 0   // 19dd
constexpr char ALPHA[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int c2d(char c){
	if (c <= '9') return c - '0';
	return c - 'A' + 10;
}

typedef enum {
	eR=0, eD,
    eL, eU,
    eDIR_LEN
} Dir_e;
constexpr int DIR[eDIR_LEN][2] = {
    {0,1}, {1,0},
    {0,-1}, {-1,0}
};
constexpr int N_DIR[eDIR_LEN] = {eL, eU, eR, eD};
#endif // 0

class ProbSolv
{
public:
    ProbSolv()
    {
#if 0   // 43dd
        int numLines = 0;
        cin >> numLines;

        vstr lines;
        FOR(i, numLines){
            string line;
            std::getline(std::cin, line);
            if(line.length() == 0){
                i--;
                continue;
            }
            lines.push_back(line);
        }
#endif

#if 0   // 27dd
        int rows = 0;
        int columns = 0;
        cin >> rows;
        cin >> columns;

        vvi grid;
        FOR(i, rows){
            vi rowG;
            FOR(j, columns){
                int val;
                cin >> val;
                rowG.push_back(val);
            }
            grid.push_back(rowG);
        }
#ifdef TEST
        cout <<endl;
        FOR(i, rows){
            FOR(j, columns){
                cout << grid[i][j] << " ";
            }
            cout <<endl;
        }
#endif
#endif
        
        _Solve();
    }
    ~ProbSolv(){}

private:
    void _Solve(){

    } // _Solve()

#if 1 // 31dd
    vstr _SplitString(string line, const string &delims) {
        string::iterator newEnd = unique(line.begin(), line.end(), [] (const char &x, const char &y) {
            return x==y and x==' ';
        });

        line.erase(newEnd, line.end());

        while (line[line.length() - 1] == ' ') {
            line.pop_back();
        }

        vstr vstrSplits;

        size_t prev = 0;
        size_t pos;
        while ((pos = line.find_first_of(delims, prev)) != string::npos) {
            if (pos > prev) {
                vstrSplits.push_back(line.substr(prev, pos-prev));
            }
            prev = pos + 1;
        }

        if (prev < line.length()) {
            vstrSplits.push_back(line.substr(prev, min(pos, line.length()) - prev + 1));
        }

        return vstrSplits;
    }
#endif

};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ProbSolv ps;
    return 0;
}
