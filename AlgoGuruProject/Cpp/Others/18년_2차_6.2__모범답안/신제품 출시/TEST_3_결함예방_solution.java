import java.util.Scanner;

public class Main {

	int []a;				//	카드뒷면 숫자를 저장하는 배열
	int N;					//	카드 개수
	int M;					//	신제품용량

	public int solve() {
		int sol=0;
		//	아래 코드의 오류를 정정하세요
		for (int i = 0; i < N - 3; i++){
			for (int j = i + 1; j < N - 2; j++){
				for (int k = j + 1; k < N - 1; k++){
					for (int l = k + 1; l < N; l++){
						if (a[i] + a[j] + a[k] + a[l] == M) sol++;
					}
				}
			}
		}
		return sol;
	}

	public void inputData()  {

		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();			//	카드 개수	
		M = sc.nextInt();			//	신제품용량
		a = new int [N+1];		

		for(int i=0 ; i<N ; i++){
			a[i] = sc.nextInt();		//	카드 뒷면 점수
		}
	}

	public static void main(String[] args){
		Main m = new Main();

		m.inputData();					//	입력 함수
		int sol = m.solve();			//	문제 풀이
		System.out.println(sol);	//	정답 출력
	}
}