#include <stdio.h>
#include <stdlib.h> 
int N;	// 건물의 층수
int X[100+10]; // 층별 공급지의 위치
int Y[100+10]; // 층별 소비지의 위치
 
typedef struct
{
	int xi, yi;
}LINE;
LINE C[100+10]; 
void InputData(void){
	int i;
	scanf("%d", &N);
	for(i=0; i<N; i++) scanf("%d %d", &X[i], &Y[i]);
}
int comp(const void * a, const void * b){
	LINE *p = (LINE*)a, *q = (LINE*)b;
	if(p->yi > q->yi)return 1;
	if(p->yi < q->yi)return -1;
	return 0;
}
int Solve(void){
	int i, low, sol = 1;
	for(i=0; i<N; i++) {
		C[i].xi = X[i];
		C[i].yi = Y[i];
	}
	qsort(C, N, sizeof(C[0]), comp);
	low = C[0].yi;
	for(i=1; i<N; i++){
		if(C[i].xi > low){
			  low = C[i].yi;
			  sol++;
		}
	}
	return sol;
}

int main(void){
	int ans;
	InputData(); // 입력함수
	
	// 코드를 작성하세요
	ans = Solve();
	printf("%d\n",ans);
	
	return 0;
}