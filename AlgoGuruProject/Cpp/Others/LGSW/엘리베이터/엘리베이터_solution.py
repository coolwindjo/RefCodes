N = int(input())    # 건물의 층수
X = []	# 층별 공급지의 위치
Y = []	# 층별 소비지의 위치
for _ in range(N):
    x, y = map(int, input().split())
    X.append(x)
    Y.append(y)
    
P = [(X[i], Y[i]) for i in range(N)]
P = sorted(P, key=lambda x : x[1])

low = P[0][1]
sol = 1
for i in range(1, N):
  if P[i][0] > low :
	   low = P[i][1]
	   sol += 1
print(sol)
