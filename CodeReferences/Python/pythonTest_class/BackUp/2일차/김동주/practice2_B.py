data = []


def menu():
    n = input("이름: ")
    k = int(input("국어: "))
    e = int(input("영어: "))
    m = int(input("수학: "))
    data.append([n, k, e, m])
    s = input("계속 입력하시겠습니까(y/n)?")
    return s


def show():
    for n in data:
        print(n[0],'\t',n[1],'\t', n[2],'\t', n[3])


while 1:
    s = menu()
    if s == 'n':
        break


print("----------------------------------------------")
print("이름\t국어\t영어\t수학")
print("----------------------------------------------")
show()
print("----------------------------------------------")



