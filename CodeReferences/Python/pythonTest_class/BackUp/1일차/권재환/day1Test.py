#1. 반지름과 높이를 입력받아 다음을 구하시오
#1) 원기둥의 부피
#2) 원뿔의 부피

# rad =  int(input('반지름 :'))
# height =  int(input('높이 :'))
# pi = 3.14
#
# def cylinderVolumn(rad, heignt):
#     rst = '%.2f' %(rad**2*pi*height)
#     # rst = '%.2f' %(rst)
#     return print('반지름 부피 : ', rst)
#
# def hornVolumn(rad, height):
#     rst = '%.2f' %(float)((1/3)*(rad**2*pi*height))
#     return print('원뿔 부피 : ', rst)
#
# cylinderVolumn(rad, height)
# hornVolumn(rad, height)

#2. 하나의 도를 입력받아 화씨값을 구하시오.

# cel = int(input('섭씨온도 :'))
#
# def convertToFahrenheit(cel):
#     fah = cel * 1.8 +32
#     print('화씨온도 : ', fah)
#
# convertToFahrenheit(cel)

#3. cm을 입력받아 인치를 구하시오.

# cm = int(input('cm :'))
#
# def convertToInch(cm):
#     inch = cm * 0.393702
#     print('inch : ', inch)
#
# convertToInch(cm)

#4. km을 입력받아 마일을 구하시오
# km = int(input('km :'))
#
# def convertToMile(km):
#     mile = km * 1.609344
#     print('mile : ', mile)
#
# convertToMile(km)

#5. 2개의 정수를 입력받아 절대값의 합을 구하시오.
# a = int(input('input1 :'))
# b = int(input('input2 :'))
#
# def calculateAbs(a, b):
#     res = abs(a) + abs(b)
#     print('a와 b의 절대값의 합은 : ', res)
#
# calculateAbs(a, b)

#6. 생년월일을 입력받아 나이를 출력하시오(현재년도 2019년을 기준)

#7. 3개의 정수를 입력받아 가장 큰 값을 구하시오.
# a = int(input('input1 :'))
# b = int(input('input2 :'))
# c = int(input('input3 :'))
#
# def compareVaule(a, b, c):
#     if (a < b):
#         res = b
#     else:
#         res = a
#
#     if (res < c):
#         res = c
#     else :
#         res =res
#
#     print('가장 큰 값은 : ', res)
#
# compareVaule(a, b, c)

#8. 년도를 입력받아 띠를 구하시오(2019년은 돼지띠)
#자4 축5 인6 묘7 진8 사9 오10 미11 신0 유1 술2 해3

# year = int(input('연도를 입력하시오 : '))
#
# def checkYear(year):
#     res = year %12
#
#     if (res ==0):
#         print('원숭이띠')
#     elif (res ==1):
#         print('닭띠')
#     elif (res ==2):
#         print('개띠')
#     elif (res ==3):
#         print('돼지띠')
#     elif (res ==4):
#         print('쥐띠')
#     elif (res ==5):
#         print('소띠')
#     elif (res ==6):
#         print('호랑이띠')
#     elif (res ==7):
#         print('토끼띠')
#     elif (res ==8):
#         print('용띠')
#     elif (res ==9):
#         print('뱀띠')
#     elif (res ==10):
#         print('말띠')
#     else:
#         print('양띠')
#
# checkYear(year)

#9. 년도를 입력받아 윤년 여부를 출력하시오.
#(윤년의 조건 4로 나눠 떨어지지만 100으로 나눠 떨어지면 않됨 또는 400으로 나누어떨어짐)

year = int(input('연도를 입력하시오 : '))

def checkYear(year):
    if(year%400 ==0):
        print('윤년입니다')
    else:
        if(year%4==0):
            if(year%100!=0):
                print('윤년입니다')
            else:
                print('윤년이 아닙니다')

        else:
            print('윤년이 아닙니다')

checkYear(year)
