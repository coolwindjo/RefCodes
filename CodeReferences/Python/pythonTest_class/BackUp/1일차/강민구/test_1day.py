# 1. 반지름과 높이를 입력받아 다음을 구하시요
# 1) 원기둥의 부피
# 2) 원뿔의 부피
#
# r = input("r: ")
# h = input("h: ")
# r = int(r)
# h = int(h)
# sol_1 = r**2*3.14*4
# sol_2 = sol_1*1/3
# print('1_1:', sol_1, '1_2:', sol_2)

# 2. 하나의 도를 입력받아 화씨값을 구하시요
# celsius = input("Celsius: ")
# celsius = int(celsius)
# fahrenheit = celsius *1.8 +32
# print('2_1:',fahrenheit)

# 3. cm 를 입력받아 인치를 구하시요
# cm = input("cm: ")
# cm = int(cm)
# inch = cm/2.54
# print('3_1:',inch)

# 4. km 를 입력받아 마일을 구하시요
# km = input("km: ")
# km = int(km)
# mile = km*0.621371
# print('4_1:',mile)

#5. 2개의 정수를 입력받아 절대값의 합을 구하시요
# a = input("a: ")
# b = input("b: ")
# a = int(a)
# b = int(b)
# if a < 0:
#     a *= -1
# if b < 0:
#     b *= -1
# solve = a + b
# print("5_1:", solve)

#6. 생년을 입력받아 나이를 출력하시요(현재년도 2019년을 기준)
# year = input("Year of birth: ")
# year = int(year)
# age = 2019 - year
# print('6_1:', age)

#7. 3개의 정수를 입력받아 가장큰값을 구하시요.
# a = input("a: ")
# b = input("b: ")
# if b<a:
#     temp = a
#     a = b
#     b = temp
# c = input("c: ")
# if c<b:
#     temp = b
#     b = c
#     c = temp
# print("7_1:",c)

#8. 년도를 입력받아 띠를 구하시요 ( 2018년은 개띠)
#못품
# year = input("Year of birth: ")
# year = int(year)
# my = ['쥐띠', '소띠', '호랑이띠', '토끼띠', '용띠', '뱀띠', '말띠', '양띠', '원숭이띠', '닭띠', '개띠', '돼지띠']
# length = len(my)
# age = 2018-year

#9. 년도를 입력받아 윤년 여부를 출력하시요
# year = input("Year: ")
# year = int(year)
# if year % 4 == 0 and year % 100 != 0:
#     rst = True
# else:
#     rst = False
#
# if year % 400 == 0:
#     rst = True
# print("9_1:", rst)

# 10. 하나의 점수를 읽어 90~100 'A' 80~89 'B' 70~79 'C' 60~69 'D' 나머지 'F'를 딕셔너리를 이용하여 작성하시요
# score = input("Score:")
# score = int(score)
# if 90 <= score <=100:
#     grade = 'A'
# if 80 <= score <=89:
#     grade = 'A'
# if 70 <= score <=79:
#     grade = 'A'
# if 60 <= score <=69:
#     grade = 'D'
# else:
#     grade = 'F'
# print('10_1:', grade)
