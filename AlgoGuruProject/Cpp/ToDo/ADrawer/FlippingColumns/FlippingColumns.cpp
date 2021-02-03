#include "../../ProbSolvStart.h"

const size_t MAX_N = 100000 + 1;
const size_t MAX_M = MAX_N;

using namespace std;

#define TEST

size_t ComputeN(const vector< vector<int> >& A, const size_t N, const size_t M) {
	size_t rowCnt = 0U;
	FOR(i, N) {
		size_t sum = 0U;
		FOR(j, M) {
			sum += A.at(i).at(j);
#ifdef TEST
			//P_IFNOT(sum == 0, sum);
#endif
		}
		if ((sum == M) || (sum == 0U)) {
			rowCnt++;
		}
	}
	return rowCnt;
}

void FlipCol(vector< vector<int> >& A, const size_t N, const size_t col) {
	FOR(i, N) {
		A.at(i).at(col) = (A.at(i).at(col) + 1U) % 2;
	}
}

void DFS(vector< vector<int> > & A, const size_t N, const size_t M, const size_t depth, int(&arFlags)[MAX_M], size_t & maxN) {
	if (depth == M) {
		return;
	}

	if (maxN == N) {
		return;
	}

	FOR(j, M) {
		if (arFlags[j] == 0U)
		{
			FlipCol(A, N, j);
			arFlags[j] = 1U;

			const size_t n = ComputeN(A, N, M);
			if (n > maxN) {
				maxN = n;
			}

			DFS(A, N, M, depth + 1U, arFlags, maxN);

			FlipCol(A, N, j);
			arFlags[j] = 0U;
		}
	}

}

int solution(vector< vector<int> > & A) {
	// write your code in C++14 (g++ 6.2.0)
	size_t N = 0;
	size_t M = 0;
	size_t maxN = 0;
	int afFlags[MAX_M] = { 0, };

	N = A.size();
	if (W_IFNOT(N > 0)) {
		M = A.at(0).size();
	}

	DFS(A, N, M, 0U, afFlags, maxN);

	return maxN;
}
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
	vector<vector<int>> vecvecnMap;
	vector<int> vecnMap;
	FOR(j, 3){
		vecnMap.clear();
		FOR(i, 4){
			int val = 0;
			cin >> val;
			vecnMap.push_back(val);
		}
		vecvecnMap.push_back(vecnMap);
	}

	solution(vecvecnMap);

#ifdef TEST
	for(auto viMap:vecvecnMap){
		for(auto n:viMap){
			cout << n << " ";
		}
		cout << endl;
	}
#endif
	return 0;
}
