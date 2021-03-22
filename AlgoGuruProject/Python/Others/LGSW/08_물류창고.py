import sys
read = sys.stdin.readline

INF = 987654321
N,M = map(int, read().split())
A = [[INF for _ in range(N+1)] for _ in range(N+1)]
for _ in range(M):
	u,v,c = map(int, read().split())
	A[u][v] = c
	A[v][u] = c

for k in range(1,N+1):
	for i in range(1,N+1):
		for j in range(1,N+1):
			if i==j:continue
			A[i][j] = min( A[i][j], A[i][k]+A[k][j])

ans = []
for i in range(1,N+1):
	m = 0
	for j in range(1,N+1):
		if A[i][j]!=INF:
			m = max(m, A[i][j])
	ans.append(m)

print(min(ans))
