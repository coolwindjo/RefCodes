// #pragma GCC optimize("Os") 
#include "../../ProbSolvStart.h"
using namespace std;

long digitSum(long base){
	long r=base;
	long res = r;
	while (res > 0) {
		r += res%10;
		res /= 10;
	}
	return r;
}

long findSmallestDigitGenerator(long n){
	long answer = 0;
	for (long i=0;i<n;++i){
		if (digitSum(i)==n) {
			answer = i;
			break;
		}
	}
	return answer;
}

int main() {
	long N;
	cin >> N;
	Timer.On("findSmallestDigitGenerator");
	cout << findSmallestDigitGenerator(N) << endl;
	Timer.Off();
	return 0;
}
