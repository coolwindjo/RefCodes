def fn1():
    r = int(input("반지름(int):"))
    h = int(input("높이(int):"))

    res1 = 3.14*(r**2)*h
    res2 = res1 / 3

    print("원기둥 부피", res1,  "원뿔 부피", res2)

def fn2():
    degree = float(input("Degree(float):"))
    res = degree * 9 / 5 + 32
    print(res, "F")


def fn3():
    cm = float(input("cm(float):"))
    res = cm * 0.39370079
    print(res, "inch")

def fn4():
    km = float(input("km(float):"))
    res = km*0.386102
    print(res,"mile")

def fn5():
    a = int(input("value_1(int):"))
    b = int(input("value_2(int):"))

    res = abs(a) + abs(b)
    print("절대값의 합", res)

def fn6():
    birth = int(input("birth(ex.19910816):"))
    birth = 2019 - int(birth/10000)
    print("나이 : ", birth)

def fn7():
    a = int(input("value_1(int):"))
    b = int(input("value_2(int):"))
    c = int(input("value_3(int):"))

    res = max(a,b,c)
    print("max = ", res)

def fn8():
    year = int(input("year(ex.1991):"))
    if year % 12 == 0:
        print("원숭이")
    elif year % 12 == 1:
        print("닭")
    elif year % 12 == 2:
        print("개")
    elif year % 12 == 3:
        print("돼지")
    elif year % 12 == 4:
        print("쥐")
    elif year % 12 == 5:
        print("소")
    elif year % 12 == 6:
        print("호랑이")
    elif year % 12 == 7:
        print("토끼")
    elif year % 12 == 8:
        print("용")
    elif year % 12 == 9:
        print("뱀")
    elif year % 12 == 10:
        print("말")
    elif year % 12 == 11:
        print("양")


def fn9():
    year = int(input("year(int):"))
    if bool(year % 4 == 0 and year % 100 != 0) or bool(year%400 == 0):
        print("윤년입니다.")
    else:
        print("윤년이 아닙니다.")

def fn10():
    point = int(input("point(int):"))
    dic = {'A':(90,100), 'B':(80,89), 'C': (70,79), 'D' : (60, 69), 'F': (0, 59)}

    for str in dic.keys():
        range = dic[str]

        if range[0] <= point <= range[1]:
             print(str)


def fn11():
    salary=[1000,2000,3000,4000,5000]
    gen = (n for n in salary)

    for n in gen:
        print(n*(1-0.033))

def fn12():
    price = int(input("price(int):"))
    pay = int(input("pay(int):"))

    if price > pay :
        print (" more pay!!")
    else:
        res = pay - price




# fn1()
# fn2()
# fn3()
# fn4()
# fn5()
# fn6()
# fn7()
# fn8()
# fn9()
# fn10()
# fn11()
# fn12()
