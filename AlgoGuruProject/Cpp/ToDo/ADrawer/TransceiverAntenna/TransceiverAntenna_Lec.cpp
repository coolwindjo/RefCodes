#include <iostream>
using namespace std;

int N;//송수신 안테나 수
int H[100000 + 10];//송수신 안테나 높이
//FA stack
int stack[100000 + 10];
int sp;
void push(int h) { stack[++sp] = h; }
int top() { return stack[sp]; }
void pop() { sp--; }
int empty() { return sp == 0; }
void InputData(){
	cin >> N;
	for (int i = 0; i < N; i++) cin >> H[i];
}
int SolveN2(){
    int cnt = 0;
    for (int i=0; i<N; i++){
        int h = 0;
        for (int j=i+1; j<N; j++){
            if (h < H[j]){
                cnt++;
                h = H[j];
            }
            if (H[i] <= H[j]) break;//가지치기
        }
    }
    return cnt;
}
int Solve(){
    int cnt = 0;
    for (int i=0; i<N; i++){
        //1.스택에서 낮은 높이는 pop시키기 & 통신 가능 개수 증가
        while (!empty() && (top() < H[i])){
            cnt++;
            pop();
        }
        //2.스택에 비어있지 않다면 통신 가능 개수 1 증가
        if (!empty()){
            cnt++;
            if (top() == H[i]) pop();
        }
        //3.i번 높이는 스택에 저장
        push(H[i]);
    }
    return cnt;
}
int main(){
	int ans = -1;
	InputData();//	입력 함수

	//ans = SolveN2();//	코드를 작성하세요
	ans = Solve();

	cout << ans << endl;//출력
	return 0;
}