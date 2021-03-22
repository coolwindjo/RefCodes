import sys
from collections import deque
sys.setrecursionlimit(10**4)
read = sys.stdin.readline

INF = 987654321
dir = [[0,1], [0,-1],[1,0],[-1,0]]
N,M = map(int, read().split())
board = []
for _ in range(N):
	board.append(list(map(int,read().split())))

def dfs(y,x):
	board[y][x] = 2
	for dy,dx in dir:
		ny,nx = y+dy, x+dx
		if 0<=ny<N and 0<=nx<M and board[ny][nx]==1:
			dfs(ny,nx)

def bfs(sy,sx):
	dist = [[INF for _ in range(M)] for _ in range(N)]
	dist[sy][sx]=0
	Q = deque()
	Q.append([sy,sx])
	while Q:
		y,x = Q.popleft()
		if board[y][x]==1:
			return dist[y][x]-1
		for dy,dx in dir:
			ny,nx = y+dy, x+dx
			if 0<=ny<N and 0<=nx<M and board[ny][nx]!=2 and dist[ny][nx]>dist[y][x]+1:
				dist[ny][nx]=dist[y][x]+1
				Q.append([ny,nx])
	return INF

flag = False
for i in range(N):
	for j in range(M):
		if board[i][j]==1:
			dfs(i,j)
			flag = True
			break
	if flag:break

ans = INF
for i in range(N):
	for j in range(M):
		if board[i][j]==2:
			ans = min(ans, bfs(i,j))

print(ans)

