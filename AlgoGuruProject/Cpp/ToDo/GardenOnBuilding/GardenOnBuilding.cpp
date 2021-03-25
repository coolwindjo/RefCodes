#if 0
#define TEST
#endif // 1
#if 0
#define SPLIT_DEBUG
#endif // 1

#include "../../ProbSolvStart.h"

class ProbSolv
{
	vll m_vllH;
	int m_N;
public:
    ProbSolv()
    {
		cin >> m_N;
		FOR(i, m_N){
			ll in;
			cin >> in;
			m_vllH.push_back(in);
		}
		
        _Solve();
    }
    ~ProbSolv(){}

private:
    void _Solve(){
		vll vllStack;
		ll bdCnt = 0;
		for (auto h : m_vllH){
#ifdef TEST
			cout << "putting H:" << h<<endl;
#endif
			while ((!vllStack.empty())
				&& (h >= vllStack.back())){
				vllStack.pop_back();
			}
			bdCnt += vllStack.size();
			vllStack.push_back(h);
#ifdef TEST
			_Print(vllStack);
#endif
		}
		cout << bdCnt;
    } // _Solve()

	void _Print(const vll &vllList){
		for (auto it : vllList){
			cout << it << " ";
		}
		cout << endl;
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
