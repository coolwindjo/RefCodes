#include <stdio.h>

int a[50+10];		//	카드뒷면 숫자를 저장하는 배열
int N;					//	카드 개수
int M;					//	신제품용량
int sol;				//	정답

int main(void){
	int i, j, k, l;
	scanf("%d %d", &N, &M);
	for (i = 0; i < N; i++) scanf("%d", &a[i]);

	//	아래 코드의 오류를 정정하세요
	for (i = 0; i < N - 3; i++){
		for (j = i + 1; j < N - 2; j++){
			for (k = j + 1; k < N - 1; k++){
				for (l = k + 1; l < N; l++){
					if (a[i] + a[j] + a[k] + a[l] == M) sol++;
				}
			}
		}
	}
	printf("%d", sol);	//	정답 출력
	return 0;
}