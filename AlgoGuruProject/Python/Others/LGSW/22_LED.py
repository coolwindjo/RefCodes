N = int(input())
A = list(input().split())
B = []
pre = A[0]
cnt=1
for i in range(1,len(A)):
	if pre!=A[i]:
		cnt+=1
	else:
		B.append(cnt)
		cnt=1
	pre=A[i]
B.append(cnt)

ans = 0
if len(B)<3:
	print(N)
else:
	for i in range(2,len(B)):
		ans = max(ans, B[i-2]+B[i-1]+B[i])
	print(ans)
	