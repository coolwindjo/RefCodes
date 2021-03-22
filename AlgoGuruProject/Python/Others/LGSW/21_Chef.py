N = int(input())
A = list()
maxt = 0
for _ in range(N):
	p,t = map(int,input().split())
	maxt = max(maxt,t)
	A.append([t,p])
A.sort()
ans = 0
S = list()
for t in reversed(range(1,maxt+1)):
	while A and A[-1][0]>=t:
		S.append(A.pop()[1])
	if S: 
		m = max(S)
		ans += m
		S.remove(m)
print(ans)
