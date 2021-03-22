import sys
read = sys.stdin.readline

N = int(read())
A = []
for _ in range(N):
	A.append(list(map(int, read().split())))

B = []
for idx in range(1,1<<N):
	t1,t2,cnt = 1,0,0
	for i in range(N):
		if (idx&(1<<i))!=0:
			t1 *= A[i][0]
			t2 += A[i][1]
			cnt +=1
	B.append([abs(t1-t2),cnt])
B.sort()
print(N-B[0][1])
		
		
