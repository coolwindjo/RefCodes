# 1. 반지름과 높이를 입력받아 다음을 구하시요
# 1) 원기둥의 부피
# 2) 원뿔의 부피

# radius = input("반지름 = ")
# radius= int(radius)
# height = input("높이 = ")
# height= int(height)
# cylinder=3.14*radius**2*height
# print("cylinder_volume = ", cylinder)
# corn=3.14*radius**2*height/3
# print("corn_volume = ", corn)

#2. 하나의 도를 입력받아 화씨값을 구하시요
# C=input("섭씨 온도를 입력하세요 = ")
# C=float(C)
# F=C*1.8+32
# print("C=",F)

#3. cm 를 입력받아 인치를 구하시요
# cm = input("insert length (cm) = ")
# cm = float(cm)
# inch = cm*0.393701
# print("converted length (inch) = ",inch)

#4. km 를 입력받아 마일을 구하시요
# km = input("insert distant (km) = ")
# km = float(km)
# mile = km*0.621371
# print("converted distant (mile) = ",mile)

#5. 2개의 정수를 입력받아 절대값의 합을 구하시요
# num1 = input("insert num1 = ")
# num2 = input("insert num2 = ")
# num1= int(num1)
# num2= int(num2)
#
# if num1 > 0:
#     num1=num1
# else:
#     num1=-num1
#
# if num2 > 0:
#     num2=num2
# else:
#     num2=-num2
#
# print("abs_sum = ", num1+num2)

#6. 생년을 입력받아 나이를 출력하시요(현재년도 2018년을 기준)
# birth = input("insert birth year=  ")
# birth = int(birth)
# age = 2020-birth+1
# print("your age =  ", age)

#7. 3개의 정수를 입력받아 가장큰값을 구하시요.
# num1 = input("insert num1 = ")
# num2 = input("insert num2 = ")
# num3 = input("insert num3 = ")
# num1= int(num1)
# num2= int(num2)
# num3= int(num3)
#
# max_num=0;
# if num1 > num2:
#     max_num = num1
# else:
#     max_num = num2
#
# if num2 > num3:
#     max_num = num2
# else:
#     max_num = num3
#
# print("max number = ",max_num)

# 10. 하나의 점수를 읽어 90~100 'A' 80~89 'B' 70~79 'C' 60~69 'D' 나머지 'F'
# 를 딕셔너리를 이용하여 작성하시요
# score = int(input("insert score:"))
# tbl = {10:'A', 9:'A', 8:'B', 7:'C', 6:'D'}
# q=score//10
# print(tbl[q])

# 11. salary=[1000,2000,3000,4000,5000 ] 의 연봉데이터가 있을때 세금 3.3을 제한
# 실수령액을 제너레이터를 이용하여 작성하시요
salary=[1000, 2000, 3000, 4000, 5000]
post_sal = (n*(1-0.033) for n in salary)
for k in post_sal:
    print("net_pay = ", k)