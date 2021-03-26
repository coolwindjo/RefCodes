#if 0
#define TEST
#endif // 1
#if 1
#define SPLIT_DEBUG
#endif // 1

#include "../../ProbSolvStart.h"

class ProbSolv
{
	int m_N;
	typedef vector<i_ii> vi_ii;
	vi_ii m_vi_iiNo_RP;
	ll m_minDiff;
	int m_minCnt;
	bool m_updated;
public:
    ProbSolv()
    {
		cin >> m_N;
		FOR(i, m_N){
			int r;
			int p;
			cin >> r >> p;
			m_vi_iiNo_RP.push_back(i_ii(i, ii(r, p)));
		}
		
        _Solve();
    }
    ~ProbSolv(){}
	
	void DFS_RM_Permutation(const int numRm){
		if (numRm == 0) {
			ll mulR = 1;
			ll sumP = 0;
#ifdef TEST
			cout << "Check! ";
			int idxCnt = 0;
#endif
			for(i_ii no_rp : m_vi_iiNo_RP){
#ifdef TEST
				if (no_rp.first == -1) cout << idxCnt++ << " ";
#endif
				if (no_rp.first == -1) continue;
				const ll r = no_rp.second.first;
				const ll p = no_rp.second.second;
				mulR *= r;
				sumP += p;
			}
			ll diff = labs(mulR - sumP);
			if (diff <= m_minDiff) {
				m_minDiff = diff;
				m_updated = true;
#ifdef TEST
				cout << "mulR(" << mulR << ")sumP(" << sumP <<")\n";
#endif
			}
			return;
		}
		FOR(i, m_vi_iiNo_RP.size()){
			int no = m_vi_iiNo_RP[i].first;
			if (no == -1) continue;
			m_vi_iiNo_RP[i].first = -1;
			DFS_RM_Permutation(numRm - 1);			
			m_vi_iiNo_RP[i].first = no;	// Backtracking
		}
	}
	
	void DFS_Combination(const int begin, const int cnt, const ll mulR, const ll sumP){
		if (cnt != 0) {
			ll diff = labs(mulR - sumP);
			if ((diff < m_minDiff) || ((diff == m_minDiff) && (cnt < m_minCnt))){	// Critical!!
#ifdef TEST_OK
				cout << " (" << m_minCnt << "=>"<< cnt << ")!";
#endif
				m_minCnt = cnt;
				m_minDiff = diff;
			}
		}
		
		FOR_INC(i, begin, m_vi_iiNo_RP.size()){
			ii rp = m_vi_iiNo_RP[i].second;
#ifdef TEST
			FOR(s, cnt){
				cout << "|";
			}
			cout << i << endl;
#endif
			DFS_Combination(i+1, cnt+1, mulR*rp.first, sumP+rp.second);
#ifdef TEST
			cout << "||||||||" << begin+1 << "finished!\n";
#endif
		}
	}
	
	void DFS_OnOff(const int idx, const int cnt, const ll mulR, const ll sumP){
		if (cnt != 0) {
			ll diff = labs(mulR - sumP);
			if ((diff < m_minDiff) || ((diff == m_minDiff) && (cnt < m_minCnt))){	// Critical!!
#ifdef TEST
				cout << " (" << m_minCnt << "=>"<< cnt << ")!";
#endif
				m_minCnt = cnt;
				m_minDiff = diff;
			}
		}
		
		if (idx >= m_N) return;	// Critical!!
		
		ii rp = m_vi_iiNo_RP[idx].second;
#ifdef TEST
		FOR(s, cnt){
			cout << "|";
		}
		cout << idx << " On" << endl;
#endif
		DFS_OnOff(idx+1, cnt+1, mulR*rp.first, sumP+rp.second);
#ifdef TEST
		cout << idx << " Off" << endl;
#endif
		DFS_OnOff(idx+1, cnt, mulR, sumP);
#ifdef TEST
		cout << "||||||||" << idx+1 << "finished!\n";
#endif
	}

private:
    void _Solve(){
		m_minDiff = INF;
		m_minCnt = INF;
		//*/
		//*/
#ifdef TEST
		Timer.On("N-tree");
#endif 
		DFS_Combination(0, 0, 1, 0);
#ifdef TEST
		Timer.Off();
#endif 

		//*/
#ifdef TEST
		Timer.On("Binary-tree");
#endif 
		DFS_OnOff(0, 0, 1, 0);
#ifdef TEST
		Timer.Off();
#endif 
		//*/
		cout << m_N - m_minCnt;
		/*/
		m_updated = false;
		int maxRm = 0;
		FOR(rm, m_N-1){
			DFS_RM_Permutation(rm);
			if (m_updated){
				maxRm = rm;
				m_updated = false;
			}
		}
		cout << maxRm;
		//*/
    } // _Solve()

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
