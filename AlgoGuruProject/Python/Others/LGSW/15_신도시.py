dir = [[-1,0],[1,0],[0,-1],[0,1]]
con = [1,0,3,2]
adj = {	"1":[2,3], "2":[0,1], "3":[1,3],
"4":[1,2], "5":[0,2], "6":[0,3], "7":[0,1,3],
"8":[1,2,3], "9":[0,1,2], "A":[0,2,3], "B":[0,1,2,3] }

N = int(input())
sx,sy = map(int, input().split())
A = []
total = N*N
for _ in range(N):
	line = input()
	total -= line.count("0")
	A.append(line)

vis = [[0 for _ in range(N)] for _ in range(N)]
vcnt = 0
def dfs(y,x):
	global vcnt,N
	vis[y][x]=1
	vcnt += 1
	for d, di in enumerate(dir):
		if d not in adj[A[y][x]]: continue
		ny,nx = y+di[0], x+di[1]
		if 0<=ny<N and 0<=nx<N and vis[ny][nx]==0 and A[ny][nx]!="0":
			if con[d] in adj[A[ny][nx]]:
				dfs(ny,nx)

dfs(sy,sx)
print(total-vcnt)
	
	