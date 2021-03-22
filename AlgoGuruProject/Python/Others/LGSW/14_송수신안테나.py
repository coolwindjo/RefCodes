N = int(input())
H = list(map(int,input().split()))
S = []
ans = 0
for h in H:
	while S and S[-1]<h:
		ans += 1
		S.pop()
	if not S:
		S.append(h)
	else:
		ans += 1
		if S[-1]>h:
			S.append(h)
print(ans)