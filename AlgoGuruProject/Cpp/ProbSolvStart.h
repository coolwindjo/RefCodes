#include <bits/stdc++.h>
using namespace std;

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
    /* These functions are written to match the win32
    signatures and behavior as closely as possible.
    */
    bool _QueryPerformanceFrequency(timespec* frequency) {
        /* Sanity check. */
        assert(frequency != nullptr);
        /* gettimeofday reports to microsecond accuracy. */
        clock_getres(CLOCK_REALTIME, frequency);
        return true;
    }

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