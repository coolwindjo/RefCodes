# 1. 반지름과 높이를 입력받아 다음을 구하시요
# 1) 원기둥의 부피
# 2) 원뿔의 부피

# 2. 하나의 도를 입력받아 화씨값을 구하시요
# 3. cm 를 입력받아 인치를 구하시요
# 4. km 를 입력받아 마일을 구하시요
# 5. 2개의 정수를 입력받아 절대값의 합을 구하시요

# 6. 생년을 입력받아 나이를 출력하시요(현재년도 2018년을 기준)
# 7. 3개의 정수를 입력받아 가장큰값을 구하시요.
# 8. 년도를 입력받아 띠를 구하시요 ( 2018년은 개띠)
# 9. 년도를 입력받아 윤년 여부를 출력하시요
# (윤년의 조건 4로 나눠 떨어지지만 100으로 나눠 떨어지면 않됨 또는 400으로 나눠 떨어짐 )
# 10. 하나의 점수를 읽어 90~100 'A' 80~89 'B' 70~79 'C' 60~69 'D' 나머지 'F'
# 를 딕셔너리를 이용하여 작성하시요
# 11. salary=[1000,2000,3000,4000,5000 ] 의 연봉데이터가 있을때 세금 3.3을 제한
#실수령액을 제너레이터를 이용하여 작성하시요
#12. 상품가격과 지불액을 입력하여 거스름돈의 갯수를 최소화하도록 거스름돈을 출력하시요
#(거스름돈, 500, 100, 50, 10 원 4가지종류로 한다 )
#예) 상품가격 2160원 지불액 3000원이면 500원 1개, 100원 3개 50원1개 10원1개 로출력
#13. 하나의 정수를 입력받아 해당정수의 약수를 구하시요.

#1
# r = float(input('반지름 : '))
# h = float(input('높이 : '))
# rst = 3.14 * r**2 * h
# print(rst)
#
# #2
# def getInch(cm):
#     return cm *0.39370
#
# cm = float(input('cm 입력 : '))
# rst = getInch(cm)
# inch = float(input('반지름 : '))
# print(inch)
#
# n1 = int(input('정수1' ))
# n2 = int(input('정수2 '))
# print (n1.__abs__() + n2.__abs__())
#
#
# #6
# birth = int(input('생년 : '))
# print(2019 - birth + 1)
#
# #7
# def getMax(a,b,c):
#     if a > b :
#         if a > c :
#             return a
#         return c
#     else:
#         return b
#
# print(getMax(1,2,3))
# #
#
# year = int(input('년도 : '))
#
# ddi = {
#        0:'원숭이', 1:'축', 2:'인', 3:'돼지',
#        4:'진', 5:'사', 6:'오', 7:'미',
#        8:'신', 9:'유', 10:'술', 11:'해'
#        }
#
# va=ddi.get(year%12)
# print(va)


#11
salary = [1000, 2000, 3000, 4000, 5000]
real = (n*0.93 for n in salary)
print(next(real))
print(next(real))
print(next(real))
print(next(real))
print(next(real))

#12

def getCharge(price, pay):
    diff = price - pay
    list = [500, 100, 50 ,10,1]
    count = 0;
    for n in list:
        d = int(diff % n)
        m = int(diff // n)
        count +=m
        diff = d
        if d == 0 :
            return count
    return count


rst =getCharge(3000,1000)
print(rst)
