import sys
from heapq import *
read = sys.stdin.readline

INF = 987654321
dir = [[0,1],[0,-1],[1,0],[-1,0]]
N = int(read())
board = []
for _ in range(N):
    board.append(list(map(int,list(read().strip()))))

dist = [[INF for _ in range(N)] for _ in range(N)]
dist[0][0]=0
Q = [[0,0,0]]
while Q:
    w,y,x = heappop(Q)
    if y==N-1 and x==N-1:break
    if w>dist[y][x]:continue
    for dy,dx in dir:
        ny,nx = y+dy, x+dx
        if 0<=ny<N and 0<=nx<N and dist[ny][nx]>w+board[ny][nx]:
            dist[ny][nx] = w+board[ny][nx]
            Q.append([dist[ny][nx],ny,nx])
print(dist[N-1][N-1])
