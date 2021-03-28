#if 0
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

class ProbSolv
{
	int m_N, m_M, m_Capa;//인원, 버스수, 버스정원
	vll m_A;
public:
    ProbSolv()
    {
		InputData();//	입력 함수
		
#ifdef TEST_OK
		FOR(i, m_N){
			cout << m_A[i] << " ";
		}
#endif
        _Solve();
    }
    ~ProbSolv(){}
	
	bool IsTooShort(const ll time){
		bool isToolShort = false;
		int mCnt = 0;
		int cCnt = 0;
		
#ifdef TEST
		cout << "[" << time << "]:" <<endl;
#endif
		ll prev = m_A[0];
		FOR_INC(i, 1, m_N){
#ifdef TEST_OK
			cout << m_A[i] << " visited!" <<endl;
#endif
			if ((m_A[i] - prev) <= time){
				
#ifdef TEST_OK
				cout << m_A[i] << " can group with " << prev <<endl;
#endif
				cCnt++;
				if (cCnt == m_Capa){
					mCnt++;
#ifdef TEST_OK
					cout << " next bus #(" << mCnt << ")"<<  m_M-1 - mCnt<< " buses remained" << endl;
#endif
					cCnt = 0;
				}
			}
			else{
				mCnt++;
#ifdef TEST_OK
					cout << " next bus #(" << mCnt << ")"<<  m_M-1 - mCnt<< " buses remained" << endl;
#endif
				cCnt = 0;
				prev = m_A[i];
#ifdef TEST_OK
				cout << m_A[i] << " is the first of the group"<< mCnt <<endl;
#endif
			}
		}
		
		if (mCnt < m_M) {
#ifdef TEST_OK
				cout << mCnt << " is smaller than " << m_M <<endl;
#endif
		}
		else{
			isToolShort = true;

#ifdef TEST_OK
				cout << mCnt << " is not smaller than " << m_M <<endl;
#endif
		}
		
		return isToolShort;
	}

private:
    void _Solve(){
		ll answer = 0;
		sort(m_A.begin(), m_A.end());
		
		const ll EPS = 1;
		ll hi = m_A.back();
		ll lo = 0;
		int cnt = 0;
		while ((hi-lo) >= EPS) {
			ll mid = (hi + lo) >> 1;
#ifdef TEST
			cout << hi <<", " << lo << ", " << mid <<endl;
#endif
	
			if (IsTooShort(mid)){
				lo = mid+1;
#ifdef TEST
				cout << mid << "is too short"<<endl;
#endif
			}
			else {
				hi = mid;
				answer = hi;
#ifdef TEST
				cout << mid << "is fair enough!"<<endl;
#endif
			}
			if (cnt++ >= 100) break;
		}
		cout << answer;
    } // _Solve()

	void InputData(){
		cin >> m_N >> m_M >> m_Capa;
		for (int i=0; i<m_N; i++){
			ll a;
			cin >> a;
			m_A.push_back(a);
		}
	}
};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    ProbSolv ps;
    return 0;
}
