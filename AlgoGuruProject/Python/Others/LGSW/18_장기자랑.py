N,S,M = map(int, input().split())
A = list(range(1,N+1))
ans = []
idx = (S-1)%N
while A:
	idx = (idx - 1 + M)%len(A)
	ans.append(str(A.pop(idx)))
print(" ".join(ans))
