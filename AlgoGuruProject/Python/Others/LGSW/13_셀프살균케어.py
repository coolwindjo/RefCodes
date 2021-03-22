N,L,M = map(int, input().split())
A = []
for _ in range(M):
	A.append(list(map(int, input().split())))

def calc(y1,x1,y2,x2):
	ret = 0
	for y,x in A:
		if y1<=y<=y2 and x1<=x<=x2:
			ret += 1
	return ret
	
ans = 0
for y,x in A:
	for h in range(1,L//2):
		w = L//2-h
		for i in range(w+1):
			ans = max(ans, calc(y,x-i,y+h,x+w-i))

print(ans)