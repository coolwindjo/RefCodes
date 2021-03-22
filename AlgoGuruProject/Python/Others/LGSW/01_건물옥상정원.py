import sys
read = sys.stdin.readline
N = int(read())
A = []
ans = 0
for _ in range(N):
    x = int(read())
    if not A:
        A.append(x)
    else:
        while A and A[-1]<=x:
            A.pop()
        ans += len(A)
        A.append(x)
print(ans)
