#include "../../ProbSolvStart.h"
//#define TEST2

const int MAX_N = 100000 + 10; 

int N;//LED 수
int S[MAX_N];//LED 상태

void InputData(){
	cin >> N;
	for (int i = 0; i < N; i++){
		cin >> S[i];
		P_IFNOT(S[i] <= 1, S[i]);
		P_IFNOT(S[i] >= 0, S[i]);
	}
}

void CollectCand(const int idx, const vi &viAB, ii &iiCand, vii &viiCandList){
	if (viAB.at(idx) == S[idx]){
		if (iiCand.first != -1){
			if (iiCand.second == -1){
				iiCand.second = iiCand.first;
			}
			viiCandList.push_back(iiCand);
			iiCand = ii(-1, -1);
		}
	}
	else{
		if (iiCand.first == -1){
			iiCand.first = idx;
		}
		else{
			iiCand.second = idx;
		}
	}
}

void FindViolationPatterns(vector<vii> &vviiCandLists)
{
	S[N] = 2;
	FOR(even, 2){
		vi viAB;
		ii iiCand(-1,-1);
		vii viiCandList;
		FOR(idx, N){
			const int i = (idx + even) % 2;
			viAB.push_back(i);
			CollectCand(idx, viAB, iiCand, viiCandList);
		}
		viAB.push_back(2);
		CollectCand(N, viAB, iiCand, viiCandList);

		vviiCandLists.push_back(viiCandList);
	}
}

void CheckMaxLenRange(const ii &range, int &maxLen)
{
	const int len = (range.second-range.first-1);
	if(len > maxLen){
		maxLen = len;
#ifdef TEST2
		cout << range.first << range.second <<" "<< len << endl;
#endif
	}
}

int FindMaxLengthWithFlip(const vector<vii> &vviiCandLists)
{
#ifdef TEST
	for(vii candList : vviiCandLists){
		for(ii rangeCand : candList){
			cout << rangeCand.first  << rangeCand.second << endl;
		}
		cout <<endl;
	}
#endif
	int maxLen = 0;
	FOR(i, 2){
		ii range(-1,-1);
		int nextBegin = -1;
		const int numLoops = (int)vviiCandLists.at(i).size();
		FOR(j, numLoops){
			if(j > 0){
				range.second = vviiCandLists.at(i).at(j).first;
				CheckMaxLenRange(range, maxLen);
				range.first = nextBegin;
			}
			nextBegin = vviiCandLists.at(i).at(j).second;

#ifdef TEST2
			cout << "ij:" << i << j << "=>";
			cout << range.first << range.second <<endl;
#endif
		}

		range.second = N;
		CheckMaxLenRange(range, maxLen);
	}
	return maxLen;
}


int main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int ans = 0;

	InputData();			//	입력 함수

	//	코드를 작성하세요
	vector<vii> vviiCandLists;
	FindViolationPatterns(vviiCandLists);
	int maxLen = FindMaxLengthWithFlip(vviiCandLists);
	ans = maxLen;
	
	cout << ans << endl;	//	정답 출력
	return 0;
}
  