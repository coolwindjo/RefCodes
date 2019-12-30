def question1():
    print("Question 1")
    r = input('반지름: ')
    h = input('높이: ')
    r = float(r)
    h = float(h)
    # 반지름 * 반지름 * 원주율 * 높이
    volume1 = r**2 * h
    volume2 = r**2 * h * 1/3
    print('원기둥 부피: ', volume1, '원뿔 부피: ', volume2)


def question2():        # 섭씨 * 9/5 + 32 = 화씨
    print("Question 2")
    temp = input('섭씨온도: ')
    temp = float(temp)

    print('화씨: ', temp * 9/5 + 32)

def question3():    # 1인치 = 2.54 cm
    print("Question 3")
    cm = input('cm: ')
    cm = float(cm)
    i = cm / 2.54
    print(i, " 인치")

def question4():    # km -> mile (1km  = 0.621371 mile)
    print("Question 4")
    km = input('km: ')
    km = float(km)
    mile = km * 0.621371
    print(mile, ' mile')

def question5():
    print("Question 5")
    num1 = input('정수1: ')
    num2 = input('정수2: ')
    num1 = float(num1)
    num2 = float(num2)
    sum = abs(num1) + abs(num2)
    print('절댓값 합: ', sum)

def question6():
    print("Question 6")
    year = input('몇년생??(19xx): ')
    year = int(year)
    old = 2019 - year + 1
    print('나이: ', old)

def question7():
    print("Question 7")
    a = [int(input()), int(input()), int(input())]
    # input(int)1 100 55        # 문자열
    print(a)
    print(max(a))

def question8():
    print("Question 8")
    year = int(input('년도(19xx): '))
    animal_list = ['돼지', '개', '닭', '원숭이', '양', '말', '뱀', '용', '토끼', '호랑이', '소', '쥐']
    old = 2019 - year + 1
    loc = old % 12 -1
    animal = animal_list[loc]
    print("You are ", animal, "띠")

def question9():
    print("Question 9")
    year = int(input('윤년 여부(19xx): '))
    print("윤년이 ", year%4==0 and ((year%100>0) or (year%400==0)))

def question10():
    print("Question 10")
    score = int(input())

def question11():
    print("Question 11")
    salary = [1000, 2000, 3000, 4000, 5000]
    real = [n*0.967 for n in salary]
    print("실수령액: ", real)

def question12():
    print("Question 12")

    print("상품가격: ")
    score = int(input())
    print(": ")
    score = int(input())


def question13():
    print("Question 13")
    num = int(input("수? "))
    for i in range(1, num + 1):
        if num % i == 0:
            print(i, end=' ')

# question1()
# question2()
# question3()
# question4()
# question5()
# question6()
question7()
# question8()
# question9()
# question10()
# question11()
# question12()
# question13()
