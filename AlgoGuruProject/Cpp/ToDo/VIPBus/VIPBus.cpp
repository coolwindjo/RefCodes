#if 0
#define TEST
#endif // 1

#include "../../ProbSolvStart.h"

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
				
#ifdef TEST
				cout << m_A[i] << " can group with " << prev <<endl;
#endif
				cCnt++;
				if (cCnt == m_Capa){
					mCnt++;
#ifdef TEST
					cout << " next bus #(" << mCnt << ") "<<  m_M-1 - mCnt<< " buses remained" << endl;
#endif
					cCnt = 0;
				}
			}
			else{
				mCnt++;
#ifdef TEST
				cout << " next bus #(" << mCnt << ") "<<  m_M-1 - mCnt<< " buses remained" << endl;
#endif
				cCnt = 0;
				prev = m_A[i];
#ifdef TEST
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
		ll lo = -1;
		int cnt = 0;
		while ((hi-lo) > EPS) {
			ll mid = (hi + lo) >> 1;
#ifdef TEST
			cout << hi <<", " << lo << ", " << mid <<endl;
#endif
	
			if (IsTooShort(mid)){
				lo = mid;
#ifdef TEST
				cout << mid << " is too short"<<endl;
#endif
			}
			else {
				hi = mid;
				answer = hi;
#ifdef TEST
				cout << mid << " is fair enough!"<<endl;
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
    int numTCs = 0;
    cin >> numTCs;
    FOR (tc, numTCs) {
        cout << "#" << tc+1 <<" ";
        ProbSolv ps;
        cout << endl;
    }
    return 0;
}
