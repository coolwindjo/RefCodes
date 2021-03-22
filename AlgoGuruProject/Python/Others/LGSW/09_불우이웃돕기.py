import sys
read = sys.stdin.readline

base = [0,1,5,10,50,100,500,1000,3000,6000,12000]
N = int(read())
num = [0] + list(map(int,read().split()))
psum = [0 for _ in range(11)]
box = [0 for _ in range(11)]
for i in range(1,11):
    psum[i] = psum[i-1] + base[i]*num[i]

for i in range(10,0,-1):
    while N>psum[i-1] and num[i]>0:
        N -= base[i]
        num[i] -= 1
        box[i] += 1

print(sum(box))
print(" ".join(map(str,box[1:])))
