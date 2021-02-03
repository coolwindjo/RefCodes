#include <iostream>
using namespace std;

int N;//정사각형 지도 크기
int X,  Y;//수돗물 공급되는 시작 좌표,  가로,  세로
int map[20][20];//지도 정보
int visited[20][20];
int pipe;
//0:상,  1:하,  2:좌,  3:우
int dh[] = {-1,  1,  0,  0};
int dw[] = {0,  0,  -1,  1};
int A[][4] ={   {0,  0,  0,  0}, //0
                {0,  0,  1,  1}, //1
                {1,  1,  0,  0}, //2
                {0,  1,  0,  1}, //3
                {0,  1,  1,  0}, //4
                {1,  0,  1,  0}, //5
                {1,  0,  0,  1}, //6
                {1,  1,  0,  1}, //7
                {0,  1,  1,  1}, //8
                {1,  1,  1,  0}, //9
                {1,  0,  1,  1}, //A(10)
                {1,  1,  1,  1}};//B(11)
void FloodFill(int h,  int w){
    visited[h][w]=1;//방문표시
    pipe--;//연결된 파이프 제거
    int cur = map[h][w];
    for (int dir=0; dir<4; dir++){//상하좌우
        int nh = h + dh[dir];
        int nw = w + dw[dir];
        if ((nh<0)||(nh>=N)||(nw<0)||(nw>=N)) continue;//범위 벗어남,  skip
        if (visited[nh][nw] == 1) continue;//이미 방문했음
        if (A[cur][dir] == 0) continue;//해당 방향으로 연결 안되어있음,  skip
        int next = map[nh][nw];
        if (A[next][dir^1] == 0) continue;//갈곳 격자의 파이프가 (h, w)랑 연결 안되어있음,  skip
        FloodFill(nh,  nw);
    }
}
void Input_Data(void){
	char str[20];
	cin >> N;
	cin >> X >> Y;
	pipe = 0;
	for (int i = 0; i < N; i++){
		cin >> str;
		for(int j = 0; j < N; j++){
			if(str[j] < 'A') map[i][j] = str[j] - '0';
			else map[i][j] = str[j] - 'A' + 10;
			if (map[i][j] != 0) pipe++;//파이프 개수 파악
		}
	}
}
int Solve(){
    FloodFill(Y,  X);
    return pipe;
}
int main(){
	int ans = -1;
	Input_Data();		//	입력 함수

	//	코드를 작성하세요
	ans = Solve();

	cout << ans << endl;	//	정답 출력
	return 0;
}
