import java.util.Scanner;

public class Main {
	int N;
	int A[] = new int [30 + 10];
	int sol[] = new int [30 + 10];
	
	void InputData(){
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		for (int i = 0; i < N; i++) A[i] = sc.nextInt();
		sc.close();
	}
	
	void OutputData(){
		System.out.println(N);
		for(int i=0;i<N;i++){
			System.out.print(sol[i] + " ");
		}
		System.out.println();
	}
	
	void Solve(){
	    int i, j, index = 0;
	    for(i=0;i<N;i++){
	        for(j=0;j<N;j++){
	            if(sol[index] == 0) break;
	            index = (index + 1) % N;
	        }
	        sol[index] = A[i];
	        index = (index + A[i]) % N;
	    }
	}

	public static void main(String[] args){
		Main m = new Main();

		m.InputData();				//	입력 함수

		m.Solve();//	코드를 작성하세요

		m.OutputData();//출력
	}
}