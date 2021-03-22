import sys
read = sys.stdin.readline

N,T = map(int, read().split())
A = []
for _ in range(N):
	A.append(list(map(int, read().split())))

B = []
for p,s in A:
	B.append(p+T*s)

B.reverse()
pre = B[0]
C = {pre}
for b in B:
	if pre>b:
		C.add(b)
		pre=b

print(len(C))
	