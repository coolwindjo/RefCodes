def first():
    r = input("input radius: ")
    r = float(r)
    h = input("input height: ")
    h = float(h)

    print("원기둥의 부피: ", r**2*3.14*h)
    print("원뿔의 부피: %.2f" % (r**2*3.14*h/3))


def second():
    c = input("input Celsius: ")
    c = float(c)
    f = 9/5*c + 32
    print("Degree in Fahrenheit is %.2f" % f)


def third():
    cm = input("input a num in cm: ")
    cm = float(cm)
    inc = cm/2.54
    print(f'the number in inch is = {inc}')


def forth():
    km = input("input a num in km: ")
    km = float(km)
    mile = km/1.609344
    print('the number in mile is %.2f' % mile)


def fifth():
    # n1 = input('input first num: ')
    # n1 = int(n1)
    # n2 = input('input second num: ')
    # n2 = int(n2)
    n1, n2 = map(int, input('input two nums: ').split())
    abs_sum = abs(n1) + abs(n2)
    print('absolute summation: ', abs_sum)


def sixth():
    year = input('input a year: ')
    year = int(year)
    age = (2019-year+1)
    print('Your age is ', age)


def seventh():
    # a = int(input('input num1: '))
    # b = int(input('input num2: '))
    # c = int(input('input num3: '))
    a, b, c = map(int, input('input three nums: ').split())
    print("max is %d" % max(a, b, c))


def eighth():
    sign = ['원숭이', '닭', '개', '돼지', '쥐', '소', '호랑이', '토끼', '용', '뱀', '말', '양']
    # print(sign)
    year = int(input('input your birth year: '))
    loc = year%12
    print("your sign is ", sign[loc])


def ninth():
    year = int(input('input a year: '))
    if (year%4 == 0 and year%100 != 0) or (year%400 == 0):
        print("Year(%d) is lunar year" %year)
    else:
        print("It's normal")


def tenth():
    # dt = {'A': 90, 'B': 80, 'C': 70, 'D': 60, 'F': 0}
    grade = {10: 'A', 9: 'B', 8: 'C', 7: 'D'}
    score = int(input("input your score: "))
    # print(grade[jumsu//10])
    print(grade.get(score//10, 'F'))
    # in_score = int(input("input your score: "))
    #
    # for k, v in dt.items():
    #     if v == 90:
    #         if v <= in_score <= v+10:
    #             print('Your grade is ', k)
    #     else:
    #         if v <= in_score < v+10:
    #             print('Your grade is ', k)


def eleventh():
    salary = [1000, 2000, 3000, 4000, 5000]
    real = (n*0.967 for n in salary)
    for n in real:
        print(n)


def twelfth():
    price = int(input('input a price: '))
    pay = int(input('input how much paid: '))

    if pay<=price:
        print('No changes...')
    else:
        change = pay - price
        a = (change//500)
        b = (change%500//100)
        c = (change%100//50)
        d = (change%50//10)
        print('your changes are %d(500)+%d(100)+%d(50)+%d(10)'%(a,b,c,d))


def thirtieth():
    num = int(input('input a num: '))
    for n in range(1, num+1):
        if num % n == 0:
            print(n, end=' ')

if __name__ == '__main__':
    # first()
    # second()
    # third()
    # forth()
    # fifth()
    # sixth()
    # seventh()
    # eighth()
    # ninth()
    tenth()
    # eleventh()
    # twelfth()
    # thirtieth()
