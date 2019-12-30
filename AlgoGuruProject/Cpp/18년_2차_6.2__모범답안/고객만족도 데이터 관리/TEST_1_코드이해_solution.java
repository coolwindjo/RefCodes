import java.util.Scanner;

public class Main {
	
	int M;		// 반복 인정 회수
	char[] S;	// 조사 문자열
	
	void inputData() {

		Scanner sc = new Scanner(System.in);
		
		M = sc.nextInt();
		S = (sc.next() + "\0").toCharArray();	
		
		sc.close();
	}

	void print_short(char c, int cnt) {
		System.out.printf("%c(%d)", c, cnt);
	}

	void print_raw(char c, int cnt) {
		int i;
		for (i = 0; i < cnt; i++) {
			System.out.printf("%c", c);
		}
	}

	void Solve() {
		int i;			// 문자열 S의 어떤 문자를 지시
		int len;		// 문자열 S의 길이
		char r_char;	// 반복되는 문자
		int r_cnt;		// 반복 회수
		
		// 코드 구현 및 결과 출력
		
		// 조사 문자열의 길이 len을 계산
		len = S.length;

		// 문자열의 첫 문자 처리
		r_char = S[0];
		r_cnt = 1;

		// 문자열의 둘째 문자부터 처리
		for (i = 1; i < len; i++) {
			if (S[i] != r_char) {
				if (r_cnt >= M) {
					// 반복되는 구간을 압축하여 출력한다
					print_short(r_char, r_cnt);
				}
				else {
					// 반복되는 구간을 그대로 출력한다
					print_raw(r_char, r_cnt);
				}
				r_char = S[i];
				r_cnt = 1;
			}
			else {
				r_cnt++;
			}
		}		
	}

	public static void main(String[] args) {
		Main m = new Main();
		
		m.inputData();		//	입력 함수
		m.Solve();			//	문제 풀이
	}
}
