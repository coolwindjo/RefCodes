#include <iostream>
#include <queue>
using namespace std;
inline const int WarnIfNot(const int condFlag, const char* condition){
	if (condFlag == 0){
		cout << "Warning: [" << condition << "] is violated!\n";
	}
	return condFlag;
}
#define W_IFNOT(condition) WarnIfNot((condition), (#condition))
#define FOR(i, size) for (int (i)=0; (i)<(size); (i)++)
#define OOR(val, min, max) (((val) < (min)) || ((val) > (max)))

typedef pair<int, int> ii;
typedef queue<ii> qii;

const int MAX_N = 10 + 1;
int N;//정사각형 지도 크기
int X, Y;//수돗물 공급되는 시작 좌표, 가로, 세로
int map[MAX_N][MAX_N];//지도 정보

int numPipes = 0;
void Input_Data(void){
	char str[20];
	cin >> N;
	cin >> X >> Y;
	for (int i = 0; i < N; i++){
		cin >> str;
		for(int j = 0; j < N; j++){
			if(str[j] < 'A')
				map[i][j] = str[j] - '0';
			else map[i][j] = str[j] - 'A' + 10;
			if (map[i][j] != 0) numPipes++;
		}
	}
}
enum eDir{
	eD = 0,
	eR,
	eU,
	eL,
	NUM_DIRS
};
const int NUM_PIPE_KINDS = 12;
const int N_DIR[NUM_DIRS] = {eU, eL, eD, eR};
const int DIR[NUM_DIRS][2] = {{1,0},{0,1},{-1,0},{0,-1}};
const int CAN_GO[NUM_PIPE_KINDS][NUM_DIRS] = {
	{0,0,0,0},
	{0,1,0,1},
	{1,0,1,0},
	{1,1,0,0},
	{1,0,0,1},
	{0,0,1,1},
	{0,1,1,0},
	{1,1,1,0},
	{1,1,0,1},
	{1,0,1,1},
	{0,1,1,1},
	{1,1,1,1},
};

int visit[MAX_N][MAX_N] = {0,};
int CheckRangeFlagPipe(const ii nextPos, const int dir){
	if (visit[nextPos.first][nextPos.second] != 0) return 0;
	if (OOR(nextPos.first, 0, N-1)) return 0;
	if (OOR(nextPos.second, 0, N-1)) return 0;
	int nextDir = N_DIR[dir];
	return CAN_GO[map[nextPos.first][nextPos.second]][nextDir];
}

int cnt = 0;
void DFS(const ii pos){
	visit[pos.first][pos.second] = ++cnt;
	FOR(dir, NUM_DIRS){
		if (CAN_GO[map[pos.first][pos.second]][dir] == 0) continue;
		ii nextPos(pos.first+DIR[dir][0], pos.second+DIR[dir][1]);
		if (CheckRangeFlagPipe(nextPos, dir)){
			DFS(nextPos);
		}
	}
}

qii iiPosQ;
void BFS(const ii start){
	visit[start.first][start.second] = ++cnt;
	iiPosQ.push(start);
	while(!iiPosQ.empty()){
		ii pos = iiPosQ.front(); iiPosQ.pop();
		FOR(dir, NUM_DIRS){
			if (CAN_GO[map[pos.first][pos.second]][dir] == 0) continue;
			ii nextPos(pos.first+DIR[dir][0], pos.second+DIR[dir][1]);
			if (CheckRangeFlagPipe(nextPos, dir)){
				visit[nextPos.first][nextPos.second] = ++cnt;
				iiPosQ.push(nextPos);
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int ans = -1;
	Input_Data();		//	입력 함수

	//	코드를 작성하세요
	//DFS(ii(Y,X));
	BFS(ii(Y,X));
	
	ans = numPipes - cnt;
	
	cout << ans << endl;	//	정답 출력
	return 0;
}
