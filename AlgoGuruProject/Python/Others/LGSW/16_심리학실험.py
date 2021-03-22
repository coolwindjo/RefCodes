N = int(input())
A = list(map(int,input().split()))
l,r = 0,N-1
ans = 2000000000
p1,p2 = -1,-1
while l<r and ans>0:
	val = A[l]+A[r]
	if abs(val)<ans:
		ans = abs(val)
		p1=l
		p2=r
	if val<0:
		l+=1
	else: 
		r-=1
print(p1,p2)

