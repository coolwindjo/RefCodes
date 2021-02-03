#include <bits/stdc++.h>
using namespace std;

#define FOR_INC(i, from, to) for(int (i)=(from); (i)<(to); ++(i))
#define FOR_DEC(i, from, to) for(int (i)=(to)-1; (i)>=(from); --(i))
#define FOR(i, to) FOR_INC((i), 0, (to))
#define OOR(x, min, max) (((x) < (min) || (x) > (max)))

static const int WarnIfNot(const int condFlag, const char* condition){
 	if (condFlag == 0) {
        cout << "Warning: [" << condition << "] is violated!\n";
    }
    return condFlag;
}
#define W_IFNOT(cond) WarnIfNot((cond), (#cond))
#define P_IFNOT(cond, var) if (!W_IFNOT(cond)) cout << "= " << var <<endl;

typedef long long ll;
constexpr int INF = 987654321;

typedef vector<string> vstr;
typedef vector<vstr> vvstr;
typedef pair<int, string> i_str;
typedef vector<i_str> vistr;
typedef vector<char> vc;
typedef vector<vc> vvc;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, ii> i_ii;
typedef queue<ii> qii;
typedef queue<int> qi;
// #include "../../ProbSolvStart.h"

const int MAX_N = 10 + 1;
int N;//정사각형 지도 크기
int X, Y;//수돗물 공급되는 시작 좌표, 가로, 세로
int g_map[MAX_N][MAX_N];//지도 정보

int numPipes = 0;
void Input_Data(void){
	char str[20];
	cin >> N;
	cin >> X >> Y;
	for (int i = 0; i < N; i++){
		cin >> str;
		for(int j = 0; j < N; j++){
			if(str[j] < 'A')
				g_map[i][j] = str[j] - '0';
			else g_map[i][j] = str[j] - 'A' + 10;
			if (g_map[i][j] != 0) numPipes++;
		}
	}
}
enum eDir{
	eD = 0,	// 00 -> 10 U
	eR,		// 01 -> 11 L
	eU,		// 10 -> 00 D
	eL,		// 11 -> 01 R
	NUM_DIRS
};
const int NUM_PIPE_KINDS = 12;
// const int N_DIR[NUM_DIRS] = {eU, eL, eD, eR};
const int DIR[NUM_DIRS][2] = {{1,0},{0,1},{-1,0},{0,-1}};
const int CAN_GO[NUM_PIPE_KINDS][NUM_DIRS] = {
	// {D, R, U, L}
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
int CheckRangeFlagPipe(const ii nextPos, const int curDir){
	if (visit[nextPos.first][nextPos.second] != 0) return 0;
	if (OOR(nextPos.first, 0, N-1)) return 0;
	if (OOR(nextPos.second, 0, N-1)) return 0;
	// int nextDir = N_DIR[curDir];
	int nextDir = curDir^2;
	return CAN_GO[g_map[nextPos.first][nextPos.second]][nextDir];
}

int cnt = 0;
void DFS(const ii pos){
	visit[pos.first][pos.second] = ++cnt;
	FOR(dir, NUM_DIRS){
		if (CAN_GO[g_map[pos.first][pos.second]][dir] == 0) continue;
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
			if (CAN_GO[g_map[pos.first][pos.second]][dir] == 0) continue;
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
