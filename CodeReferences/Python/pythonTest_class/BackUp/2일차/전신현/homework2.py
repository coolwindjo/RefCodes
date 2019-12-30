
allData = []
oneData = []

response = 'y'

while(response == 'y'):

    oneData = []

    name = str(input("이름:"))
    kor = int(input("국어:"))
    eng = int(input("영어:"))
    math = int(input("수학:"))

    oneData.append(name)
    oneData.append(kor)
    oneData.append(eng)
    oneData.append(math)

    allData.append(oneData)

    response = str(input("계속 입력하시겠습니까?(y/n):"))

print("-" * 20)
print("{} {} {} {}".format("이름","국어","영어","수학"))
print("-" * 20)
for info in allData:
    print("{}    {}    {}    {}".format(info[0],info[1],info[2],info[3]))
print("-" * 20)


