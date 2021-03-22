N = int(input())
A = list(input().split())
SC = dict()
for name in A:
	SC[name] = 0

M = int(input())
for _ in range(M):
	name,s = input().split()
	score = int(s)
	if SC.get(name, -1) != -1:
		SC[name] += score

B = []
for i,v in enumerate(A):
	B.append([i, SC[v]])
B.sort(key=lambda x: [-x[1], x[0]])
for i in range(3):
	print(A[B[i][0]], B[i][1])
	