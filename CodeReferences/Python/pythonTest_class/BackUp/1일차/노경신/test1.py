#반지름 높이를 받아
pi = 3.14

def cylinder(r, h):
    return r**2*h*pi

print("1번 문제", cylinder(2, 3))

def CtoF(c):
    return (c * 9) / 5 + 32

print("2번 문제", CtoF(10))

def cmToInch(d):
    return d / 2.54

print("3번 문제", cmToInch(10), "inch")

def kmToMile(km):
    return km/1.524

print("4번 문제", kmToMile(150), "mile")

def absolute(e1, e2):
    if e1 < 0:
        e1 *= -1
    if e2 < 0:
        e2 *= -1
    return e1 + e2

print("5번 문제", absolute(-5, -7), "절대값의 합")

def yearToAge(year):
    return 2018 - year + 1

print("6번 문제", yearToAge(1976), "나이")

def maxOfThree(f1, f2, f3):
    return max(f1, f2, f3)

print("7번 문제", maxOfThree(2, 3, 4), "최대값")

def yearToAnimal(year):
    if year % 12 == 2:
        yta = "원숭이띠"
    elif year % 12 == 1:
        yta = "닭띠"
    elif year % 12 == 0:
        yta = "개띠"
    elif year % 12 == 3:
        yta = "돼지띠"
    elif year % 12 == 4:
        yta = "쥐띠"
    elif year % 12 == 5:
        yta = "소띠"
    elif year % 12 == 6:
        yta = "호랑이띠"
    elif year % 12 == 7:
        yta = "토끼띠"
    elif year % 12 == 8:
        yta = "용띠"
    elif year % 12 == 9:
        yta = "뱀띠"
    elif year % 12 == 10:
        yta = "말띠"
    elif year % 12 == 11:
        yta = "양띠"

    return yta

print("8번 문제", yearToAnimal(int(1976)))

def yy(year):
    yy2 = ((year % 400) == 0 or ((year % 4) == 0 and (year % 100 != 0)))
    if yy2 == 1:
        result = '윤년'
    else:
        result = '평년'
    return result

print("9번 문제", yy(2020))

def score(scr):
    s = {'A': 90, 'B': 80, 'C':70, 'D':60}
    for n in s.values():
        if scr > n:
            print("here", s.keys())
            break

print("10번 문제", score(95), "점")