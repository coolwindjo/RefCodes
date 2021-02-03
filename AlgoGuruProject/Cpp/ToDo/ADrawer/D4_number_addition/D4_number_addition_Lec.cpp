#if 0
//다중트리로 조합구현
#include <stdio.h>
#define MAXN (20)
int N, K;//자연수 개수, 합
int A[MAXN + 1];//자연수 값
int prefixsum[MAXN + 1];//누적합
const char *msg[] = { "NO", "YES" };
void InputData() {
    scanf("%d %d", &N, &K);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        prefixsum[i] = prefixsum[i - 1] + A[i];//누적합
    }
}
int DFS(int s, int sum) {//시작 요소번호, 합(빼가는 방식), 조합
    if (sum > prefixsum[N] - prefixsum[s - 1]) return 0;//남은 수를 모두 사용해도 sum을 만들수없음, 가지치기
    if (sum < 0) return 0;//합이 음수면 실패
    if (sum == 0) return 1;//성공, K를 만들수있음
    for (int i = s; i <= N; i++) {//요소번호
        if (DFS(i + 1, sum - A[i]) == 1) return 1;//성공이 리턴되면 리턴
    }
    return 0;//실패
}
int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        //Init();
        InputData();
        int ans = DFS(1, K);
        printf("%s\n", msg[ans]);
    }
    return 0;
}
#else
//이진트리로 조합구현
#include <stdio.h>
#define MAXN (20)
int N, K;//자연수 개수, 합
int A[MAXN + 1];//자연수 값
int prefixsum[MAXN + 1];//누적합
const char *msg[] = { "NO", "YES" };
void InputData() {
    scanf("%d %d", &N, &K);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        prefixsum[i] = prefixsum[i - 1] + A[i];//누적합
    }
}
int DFS(int n, int sum) {//요소번호, 합(빼가는 방식), 조합
    if (sum > prefixsum[N] - prefixsum[n - 1]) return 0;//남은 수를 모두 사용해도 sum을 만들수없음, 가지치기
    if (sum < 0) return 0;//합이 음수면 실패
    if (sum == 0) return 1;//성공
    if (n > N) return 0;//실패
    if (DFS(n + 1, sum - A[n]) == 1) return 1;//n번째요소 포함하는 경우
    if (DFS(n + 1, sum) == 1) return 1;//n번째 요소 포함하지 않는 경우
    return 0;//실패
}
int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        //Init();
        InputData();
        int ans = DFS(1, K);
        printf("%s\n", msg[ans]);
    }
    return 0;
}
#endif
/**************************************************************
    Problem: 1326
    User: SWT01005
    Language: C++
    Result: Accepted
    Time:3 ms
    Memory:1156 kb
****************************************************************/