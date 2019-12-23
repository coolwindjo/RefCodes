#include "ProbSolvStart.h"

#if 1
#define TEST
#endif // 1

static const int WarnIfNot(const int condFlag, const char* condition){
 	if (condFlag == 0) {
        cout << "Warning: [" << condition << "] is violated!\n";
    }
    return condFlag;
}
#define W_IFNOT(cond) WarnIfNot((cond), (#cond))
#define P_IFNOT(cond, var) if (!W_IFNOT(cond)) cout << "= " << var <<endl;

typedef enum {
	eR=0, eD, eL, eU, eDIR_LEN
} Dir_e;
constexpr int DIR[eDIR_LEN][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

 	int numTCs = 0;
	cin >> numTCs;
	FOR(tc, numTCs) {
 		cout << "#" << tc + 1 << " ";
        CProbSolv ps();
    }

   return 0;
}
