def problem1():
    radius = float(input("반지름을 입력하세요: "))
    height = float(input("높이를 입력하세요: "))
    print("원기둥의 부피는 %.1f"%(radius**2 * 3.14 * height))
    print("원뿔의 부피는 %.1f"%(radius**2 * height / 3))

def problem2():
    celsius = float(input("섭씨를 입력하세요: "))
    print("화씨로 변환하면 %.1f"%(celsius*1.8 + 32))

def problem3():
    cm = float(input("cm 단위로 입력하세요: "))
    print("인치로 변환하면 %.1f"%(cm*0.393701))

def problem4():
    km = float(input("km 단위로 입력하세요: "))
    print("mile로 변환하면 %.1f"%(km*0.621371))

def problem5():
    a = int(input("정수 a를 입력하세요: "))
    b = int(input("정수 b를 입력하세요: "))
    a = a if a >= 0 else -a
    b = a if b >= 0 else -b
    print("a와 b 절대값의 합은 %d"%(a+b))

def problem6():
    birthyear = int(input("생년을 입력하세요(yyyy): "))
    print("2019년 기준으로 나이는 %d살"%(2019 - birthyear + 1))

def problem7():
    a = int(input("정수 a를 입력하세요: "))
    b = int(input("정수 b를 입력하세요: "))
    c = int(input("정수 c를 입력하세요: "))
    if a>b and a>c:
        largest = a
    if b>a and b>c:
        largest = b
    if c>a and c>b:
        largest = c
    print("셋 중 가장 큰 정수는 %d"%largest)

def problem8():
    birthyear = int(input("생년을 입력하세요(yyyy): "))
    remainder = birthyear%12
    animal = ["원숭이", "닭", "개", "돼지", "쥐", "소", "호랑이", "토끼", "용", "뱀","말", "양"]
    print("%s띠입니다."%animal[remainder])

def problem9():
    birthyear = int(input("생년을 입력하세요(yyyy): "))
    if (birthyear%4==0 and birthyear%100!=0) or (birthyear%4==0 and birthyear%100==0 and birthyear%400==0):
        leapyear = True
    else:
        leapyear = False

    if leapyear == True:
        print("윤년입니다.")
    else:
        print("윤년이 아닙니다.")

# def problem12():
#     price = int(input("상품가격을 입력하세요: "))
#     pay = int(input("지불액을 입력하세요: "))
#     remainder = pay%price

def problem13():
    num = int(input("정수를 입력하세요: "))
    print("해당 정수의 약수는 ",end='')
    a = [n for n in range(1,num+1) if num%n==0]
    print(a)

print("문제1~9, 13 풀었습니다.")
select = int(input("문제 번호를 입력하세요: "))
if select == 1:
    problem1()
elif select == 2:
    problem2()
elif select == 3:
    problem3()
elif select == 4:
    problem4()
elif select == 5:
    problem5()
elif select == 6:
    problem6()
elif select == 7:
    problem7()
elif select == 8:
    problem8()
elif select == 9:
    problem9()
# elif select == 10:
#     problem10()
elif select == 13:
    problem13()
