import sys
input = sys.stdin.readline

i2c = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
def c2i(s):
    if s<='9': return ord(s)-ord('0')
    else: return ord(s)-ord("A")+10

N = int(input())
for _ in range(N):
    base,b,c = input().split()
    if b=="0" or c=="0":
        print("0")
        continue

    base = int(base)
    flag = 1
    if b[0]=='-':
        b=b[1:]
        flag *= -1
    if c[0]=='-':
        c=c[1:]
        flag *= -1
    A = [0 for _ in range(len(b)+len(c))]
    for i,v1 in enumerate(b):
        for j,v2 in enumerate(c):
            A[i+j+1] += c2i(v1)*c2i(v2)
    A.reverse()
    for i in range(len(A)-1):
        q,r = divmod(A[i],base)
        A[i] = r
        A[i+1] += q
    A.reverse()
    if flag==-1:
        print("-", end="")
    if A[0]>0:
        print(i2c[A[0]],end="")
    for i in range(1,len(A)):
        print(i2c[A[i]],end="")
    print()