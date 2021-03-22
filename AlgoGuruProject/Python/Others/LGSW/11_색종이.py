N = int(input())
A = [input() for _ in range(N)]
pos = dict()
base ="123456789"
for i in base:
	pos[i] = [10,10,-1,-1]

for i in range(N):
	for j in range(N):
		if A[i][j]!="0":
			pos[A[i][j]][0] = min(pos[A[i][j]][0],i)
			pos[A[i][j]][1] = min(pos[A[i][j]][1],j)
			pos[A[i][j]][2] = max(pos[A[i][j]][2],i)
			pos[A[i][j]][3] = max(pos[A[i][j]][3],j)

B = [[0 for _ in range(N)] for _ in range(N)]
for b in base:
	y1,x1,y2,x2 = pos[b]
	for i in range(y1,y2+1):
		for j in range(x1,x2+1):
			B[i][j]+=1

ans = 0
for b in B:
	ans = max(ans, max(b))
print(ans)
	