#include "../../ProbSolvStart.h"

/*/
int N;
int A[30 + 10];

void InputData(){
	cin >> N;
	for(int i=0;i<N;i++){
		cin >> A[i];
	}
}

void Solve(){
	int value, cnt=0, from=0;
	cout << N << endl;
	value = A[from];
	while (cnt < N){
		while (value == 0){
			from = (from + 1) % N;
			value = A[from];
		}
		cout << value << " ";
		cnt++;
		A[from] = 0;
		from = (value + from) % N;
		value = A[from];
	}
}

int main(){
	InputData();
	Solve();
	return 0;
}

/*/

int A[30 + 10];
int sol[30 + 10];
class ProbSolv
{
    int N;
public:
    ProbSolv()
    {
        _Solve();
    }
    ~ProbSolv(){}


    void InputData(){
        cin >> N;
        for(int i=0;i<N;i++){
            cin >> A[i];
        }
    }

    //*/
    void Solve(){
        int value, cnt=0, from=0;
        value = A[from];
        FOR(cnt, N){
            //P_IFNOT(from==-1,from);
            FOR(i, N){
            if (value != 0) break;	// get next one if current is zero
                from = (from + 1) % N;
                value = A[from];
                //P_IFNOT(value==-1,value);
            }
            //P_IFNOT(from==-2,from);
            //P_IFNOT(value==-2,value);
            sol[cnt] = value;
            A[from] = 0;	// mark visited
            
            from = (value + from) % N;	//get next idx
            value = A[from];	// get the value;
            //P_IFNOT(from==-3,from);
            //P_IFNOT(value==-3,value);
        }
}
    /*/
    void Solve(){
        int i, j, index = 0;
        for(i=0;i<N;i++){
            for(j=0;j<N;j++){
                if(sol[index] == 0) break;
                index = (index + 1) % N;
            }
            sol[index] = A[i];
            index = (index + A[i]) % N;
        }
    }
    //*/

    void OutputData(){
        cout << N << endl;
        for(int i=0;i<N;i++){
            cout << sol[i] << " ";
        }
        cout << endl;
    }

private:
    void _Solve(){
	InputData();//	입력 함수

	//	코드를 작성하세요
	Solve();
	
	OutputData();//출력 
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
