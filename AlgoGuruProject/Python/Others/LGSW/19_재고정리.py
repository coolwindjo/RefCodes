from itertools import permutations

N,M = map(int,input().split())
A = list(map(int,input().split()))
num = [0]*10
psum = [[0 for _ in range(N+1)] for _ in range(M+1)]
for i, a in enumerate(A):
    num[a] += 1
    for b in range(1,M+1):
        psum[b][i+1] = psum[b][i]
        if a==b:
            psum[b][i+1] += 1

total = 0
for P in permutations(range(1,M+1)):
    idx = 0
    cnt = 0
    for p in P:
        s,e = idx, idx+num[p]
        cnt += psum[p][e]-psum[p][s]
        idx = e
    total = max(total,cnt)
print(N-total)