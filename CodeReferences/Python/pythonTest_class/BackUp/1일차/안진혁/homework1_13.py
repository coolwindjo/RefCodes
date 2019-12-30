n = int(input("정수 : "))

for d in range(n,0,-1):
    if n%d == 0:
        print(d)