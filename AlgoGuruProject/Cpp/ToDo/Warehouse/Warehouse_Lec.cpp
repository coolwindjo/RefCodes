#include <iostream>
using namespace std;
#define INF ((int)1e5)
#define MAXN (100)
int N,  M;//공장 수,  도로 정보 수
int A[5000],  B[5000],  D[5000];//공장 A,  공장 B,  거리 D
int dist[MAXN+2][MAXN+2];//공장간의 거리 배열(0이면 갈수없음)
int visited[MAXN+2];
//linear queue;
int que[MAXN * 100 + 10];
int wp,  rp;
void push(int n,  int t){
    if (visited[n] <= t) return;
    visited[n]=t; que[wp++]=n;
}
int front() { return que[rp]; }
void pop() { rp++; }
bool empty() { return wp==rp; }
int BFS(int s){
    int cur;
    //1.초기화
    wp = rp = 0;
    for (int i=1; i<=N; i++) visited[i]=INF;
    //2.시작위치 큐에 저장
    push(s,  0);
    //3.반복문
    while(!empty()){
        cur = front(); pop();
        for (int e=1; e<=N; e++){
            if (dist[cur][e] == 0) continue;//0이면 경로 없음
            push(e,  visited[cur]+dist[cur][e]);
        }
    }
    //4.결과리턴
    int idx=1;
    for (int i=2; i<=N; i++){
        if (visited[idx] < visited[i]) idx = i;
    }
    return visited[idx];
}
int Solve(){
    int sol=INF;
    //1.링크 정보를 노드간 거리 배열 생성
    for (int i=0; i<M; i++){
        int s = A[i],  e = B[i];
        dist[s][e] = dist[e][s] = D[i];//양방향이므로
    }
    //2.각 노드에서 가장 먼 공장과의 거리 구하기
    for (int s=1; s<N; s++){//출발 공장 번호
        int t = BFS(s);//s에서 가장 먼 공장과의 거리
        if (sol > t) sol = t;
    }
    return sol;
}
void InputData(){
	int i;
	cin >> N >> M;
	for (i = 0; i < M; i++){
		cin >> A[i] >> B[i] >> D[i];
	}
}
int main(){
	int ans = -1;
	InputData();//	입력 함수

	//	코드를 작성하세요
    ans = Solve();

	cout << ans << endl;//	정답 출력
	return 0;
}