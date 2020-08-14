#include <iostream>
using namespace std;
#define MAXN ((int)8e4)
int N;//건물 수
int H[80010];//건물 높이
//FA stack(LIFO)
int stack[MAXN + 10];
int sp;
void push(int h) { stack[++sp] = h; }
int top() { return stack[sp]; }
void pop() { sp--; }
int size() { return sp; }
int empty() { return sp==0; }

void Input_Data(void){
	cin >> N;
	for (int i = 0; i < N; i++){
		cin >> H[i];
	}
}
long long Solve(){
    long long cnt = 0;
    for (int i=0; i<N; i++){
        //1.stack에서 i번 건물보다 낮거나 같은 높이 건물 제거
        while (!empty() && (top() <= H[i])) {
            pop();
        }
        //2.남은 건물들이 i번 건물을 볼수있는 건물임
        cnt += size();
        //3.i번 건물이 현재 제일 앞 건물이므로
        push(H[i]);
    }
    return cnt;
}
int main(){
	long long ans = -1;
	Input_Data();		//	입력 함수

	//	코드를 작성하세요
	ans = Solve();

	cout << ans << endl;	//	정답 출력
	return 0;
}