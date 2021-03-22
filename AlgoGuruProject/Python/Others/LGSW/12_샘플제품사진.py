N = int(input())
A = []
s2 = set()
for _ in range(N):
	x,i = map(int, input().split())
	A.append([x,i])
	s2.add(i)
	
ID = dict()
cnt_id = 0
for i in sorted(list(s2)):
	ID[i]=cnt_id
	cnt_id+=1

B = []
for a,b in A:
	B.append([a, ID[b]])
B.sort()

check = [0]*cnt_id
S=0
ans=1000000000
for E in range(len(B)):
	check[B[E][1]]+=1
	while 0 not in check:
		ans = min(ans, B[E][0]-B[S][0])
		check[B[S][1]]-=1
		S+=1
print(ans)
	
