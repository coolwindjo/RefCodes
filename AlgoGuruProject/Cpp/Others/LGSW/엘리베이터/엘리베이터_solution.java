
import java.util.Arrays;
import java.util.Scanner;

public class Main {
	int N;	// 건물의 층수
	int X[] = new int [100+10]; // 층별 공급지의 위치
	int Y[] = new int [100+10]; // 층별 소비지의 위치
	public static class LINE implements Comparable<LINE>{
        int x, y;
        LINE(){}
        LINE(int x, int y){
            this.x=x; this.y=y;
        }
		@Override
		public int compareTo(LINE a) {
			return this.y - a.y; 
		} 
        
	}
	LINE C[];
	void InputData(){
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		C = new LINE[N];
		for (int i = 0; i<N; i++){
			X[i] = sc.nextInt();
			Y[i] = sc.nextInt();
		}
		sc.close();
		
	}

	int Solve(){
		int low, sol = 1;
		for(int i=0; i<N; i++) {
			C[i] = new LINE(X[i], Y[i]);
		}
		Arrays.sort(C);
		low = C[0].y;
		for(int i=1; i<N; i++){
			if(C[i].x > low){
				  low = C[i].y;
				  sol++;
			}
		}
		return sol;
	}
	public static void main(String[] args){
		Main m = new Main();

		m.InputData();	 //	입력 함수

		//	코드를 작성하세요
		int ans = m.Solve();
		System.out.println(ans);
	}
}
