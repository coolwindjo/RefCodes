#include <stdio.h>

int N;
int A[30 + 10];
int sol[30 + 10];

void InputData(void){
    int i;
    scanf("%d", &N);
    for(i=0;i<N;i++){
        scanf("%d", &A[i]);
    }
}

void OutputData(void){
    int i;
    printf("%d\n", N);
    for(i=0;i<N;i++){
        printf("%d ", sol[i]);
    }
    printf("\n");
}

void Solve(void){
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

int main(void){
    InputData();
    Solve();
    OutputData();
    return 0;
}