a = int(input("첫번째 정수 : "))
b = int(input("두번째 정수 : "))
c = int(input("세번째 정수 : "))
max = a
if max < b:
    max = b
if max < c:
    max = c
print("최대값 : ", max)

