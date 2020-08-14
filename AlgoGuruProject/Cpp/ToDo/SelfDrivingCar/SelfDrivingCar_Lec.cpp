#include <iostream>
using namespace std;
int H;//세로크기
int W;//가로크기
char map[500][510];//지도

int visited[500][510];
//linear queue
struct QUE{
    int h,  w,  t;
};
QUE que[500 * 500 + 10];
int wp,  rp;
void push(int h,  int w,  int t){
    if ((h<0) || (h>=H) || (w<0) || (w>=W)) return;//범위 벗어남
    if (map[h][w] != '.') return;//길 아님
    if (visited[h][w] == 1) return;//이미 방문 했음
    visited[h][w]=1;
    que[wp].h=h; que[wp].w=w; que[wp].t=t; wp++;
}
QUE front() { return que[rp]; }
void pop() { rp++; }
bool empty() { return wp==rp; }
int BFS(){
    int dh[] = {-1,  1,  0,  0};
    int dw[] = {0,  0,  -1,  1};
    QUE cur;
    //1.초기화
    wp = rp = 0;
    //2.시작위치 큐에 저장
    push(0,  0,  0);
    //3.반복문
    while(!empty()){
        cur = front(); pop();
        if ((cur.h == H-1) && (cur.w == W-1)) return cur.t;//도착 성공
        for (int i=0; i<4; i++){
            push(cur.h+dh[i],  cur.w+dw[i],  cur.t+1);
        }
    }
    //4.실패
    return -1;
}
void input_data(){
	int i;
	cin >> H >> W;
	for(i=0 ; i<H ; i++){
		cin >> map[i];
	}
}
int main(){
	int ans = 0;
	input_data();
	ans = BFS();//	코드를 작성하세요
	cout << ans << endl;
	return 0;
}