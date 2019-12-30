def work1():
    radius = int(input('반지름: '))
    height = int(input('높이: '))
    print('원기둥 부피: ', 3.14 * radius**2 * height)
    print('원뿔의 부피: ', 3.14 * radius**2 * height / 3)

def work2():
    temp = float(input('온도: '))
    print('화씨: ', temp * 1.8 + 32)

def work3():
    num = float(input('cm: '))
    print('인치: ', num / 2.54)

def work4():
    num = float(input('km: '))
    print('마일: ', num / 1.609)

def work5():
    num1 = int(input('정수 1: '))
    num2 = int(input('정수 2: '))

    if num1 < 0:
        num1 = num1 * -1
    if num2 < 0:
        num2 = num2 * -1

    print("합: ", num1 + num2)

def work6():
    num = int(input("생년: "))
    print("나이: ", 2019 - num + 1)

def work7():
    num1 = int(input('정수 1: '))
    num2 = int(input('정수 2: '))
    num3 = int(input('정수 3: '))
    tmp = 0

    if num1 > num2:
        tmp = num1
    else:
        tmp = num2

    if tmp < num3:
        tmp = num3

    print("제일 큰 수: ", tmp)

def work8():
    num = int(input('년도: '))
    ary = ['쥐', '소', '호랑이', '토끼', '용', '뱀', '말', '양', '원숭이', '닭', '개', '돼지']
    index = (11 - (2019 - num)) % 12
    print("띠: ", ary[index])

def work9():
    num = int(input('년도: '))

    if (num % 4 == 0 and num % 100 != 0) or num % 400 == 0:
        print('윤년')
    else:
        print('윤년아님')

# work1()
# work2()
# work3()
# work4()
# work5()
# work6()
# work7()
# work8()
work9()
