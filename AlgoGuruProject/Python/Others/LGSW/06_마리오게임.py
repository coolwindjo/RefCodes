import sys
read = sys.stdin.readline

N = int(read())
A = list(map(int,read().split()))
ans,cnt = 0,0
for i in range(N-1):
	if cnt==0 and A[i]>A[i+1]:
		ans += A[i]
		cnt = (cnt+1)%2
	elif cnt==1 and A[i]<A[i+1]:
		ans -= A[i]
		cnt = (cnt+1)%2
if cnt==0:
	ans += A[N-1]
print(ans)