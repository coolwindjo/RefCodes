#include "../../ProbSolvStart.h"

const int MAX_N = 100 + 1;
const int MAX_M = (int)((double)(MAX_N*(MAX_N-1)) * 0.5);

int N, M;//공장 수, 도로 정보 수
int A[MAX_M], B[MAX_M], D[MAX_M];//공장 A, 공장 B, 거리 D

void InputData(){
	int i;
	cin >> N >> M;
	for (i = 0; i < M; i++){
		cin >> A[i] >> B[i] >> D[i];
	}
}

int arDist[MAX_N][MAX_N];

int main(){
	int ans = -1;
	InputData();//	입력 함수

	//	코드를 작성하세요
	W_IFNOT(N > 0);
	W_IFNOT(M > 0);

	// Init
	FOR(i, N){
		FOR(j, N){
			if (i == j)
				arDist[i][j] = 0;
			else
				arDist[i][j] = INF;
		}
	}
	FOR(i, M){
		arDist[A[i]-1][B[i]-1] = D[i];
		arDist[B[i]-1][A[i]-1] = D[i];
	}
	
	// Update with Floyd
	FOR(k, N){
		FOR(i, N){
			if (arDist[i][k] == INF) continue;
			FOR(j, N){
				arDist[i][j] = min(arDist[i][j], arDist[i][k]+arDist[k][j]);
			}
		}
	}
//#define TEST
#ifdef TEST
	FOR(i, N){
		FOR(j, N){
			if (i==j)continue;
			if (arDist[i][j] == INF) continue;
			cout << i+1 << " " << j+1 << " : " << arDist[i][j] <<endl;
		}
	}
#endif //TEST
	
	// Find min worst
	int minWorst = INF;
	FOR(k, N){
		int worst = 0;
		FOR(i, N){
			if (k==i) continue;
			int& dist = arDist[k][i];
			W_IFNOT(dist > 0);
			if (dist == INF) continue;
			W_IFNOT(dist < INF);
			if (dist > worst)
				worst = dist;
		}
#ifdef TEST
		if (worst == 10)
			cout << k+1 << i+1<<endl;
#endif	//TEST
		if (worst==0) continue;
		if (worst < minWorst)
			minWorst = worst;
	}
	ans = minWorst;
	
	cout << ans << endl;//	정답 출력
	return 0;
}