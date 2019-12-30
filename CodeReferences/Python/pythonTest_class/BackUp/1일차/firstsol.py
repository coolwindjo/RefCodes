# 1. 반지름과 높이를 입력받아 다음을 구하시요
# 1) 원기둥의 부피
# 2) 원뿔의 부피
r = int( input("반지름 = ") )
h = int( input("높이 = ") )
cylinder = r**2*3.14*h
cone = cylinder/3
# 2. 하나의 도를 입력받아 화씨값을 구하시요
c = int( input(" 온도를 입력하시오(℃) : ") )
F = c*1.8+32
# 3. cm 를 입력받아 인치를 구하시요
cm = int( input("cm:") )
inch = cm*0.393701
# 4. km 를 입력받아 마일을 구하시요
km = int( input("km:") )
mile = km * 0.621371
def kmToMile( km ):
    return km * 0.621371
# 5. 2개의 정수를 입력받아 절대값의 합을 구하시요
def myabs( a, b):
    a = -1*a if a<0 else a
    b = -1*b if b<0 else b
    return a+b

# 6. 생년을 입력받아 나이를 출력하시요(현재년도 2019년을 기준)
year= 2019
nai = 2019 - year + 1
# 7. 3개의 정수를 입력받아 가장큰값을 구하시요.
def maxThree( a,b,c):
    mx = a if a>b else b
    mx = c if c>mx else mx
    return mx
# 8. 년도를 입력받아 띠를 구하시요 ( 2018년은 개띠)
year = 2019
ttee =('원숭이', '닭', '개','돼지',
       "쥐",'소', '범', '토끼','용',
       '뱀', '말', '양' )
print( ttee[year%12] )
def tteefn( year):
    return ('원숭이', '닭', '개','돼지',
       "쥐",'소', '범', '토끼','용',
       '뱀', '말', '양' )[year%12]

# 9. 년도를 입력받아 윤년 여부를 출력하시요
# (윤년의 조건 4로 나눠 떨어지지만 100으로 나눠 떨어지면 않됨 또는 400으로 나눠 떨어짐 )

year = 2019
yoon = "윤년" if year%4==0 and year%100!=0 or year%400==0 else '윤년아님'
def isYoon( year):
    return "윤년" if year%4==0 and year%100!=0 or year%400==0 else '윤년아님'

# 10. 하나의 점수를 읽어 90~100 'A' 80~89 'B' 70~79 'C' 60~69 'D' 나머지 'F'
# 를 딕셔너리를 이용하여 작성하시요
jumsu = 45
grade = {10:'A',9:'A',8:'B',7:'C',6:'D'}
# print( grade[ jumsu//10 ] )
print( grade.get(jumsu//10,'F')  )

# 11. salary=[1000,2000,3000,4000,5000 ] 의 연봉데이터가 있을때 세금 3.3을 제한
# 실수령액을 제너레이터를 이용하여 작성하시요
salary=[1000,2000,3000,4000,5000 ]
sil = ( n*(1-0.033) for n in salary )
for s in sil:
    print( s )

# 12. 상품가격과 지불액을 입력하여 거스름돈의 갯수를
# 최소화하도록 거스름돈을 출력하시요
# (거스름돈, 500, 100, 50, 10 원 4가지종류로 한다 )
# 예) 상품가격 2160원 지불액 3000원이면 500원 1개, 100원 3개 50원1개 10원1개 로출력
product = 2160
pay = 3000
exchange = pay-product
n500 = exchange//500
exchange = exchange%500
n100 = exchange//100
exchange = exchange%100
n50 = exchange//50
exchange = exchange%50
n10 = exchange//10
print("500원",n500, "100원", n100, "50원",n50,"10원",n10)

# 13. 하나의 정수를 입력받아 해당정수의 약수를 구하시요.
num = 10
yaksu = [ n for n in range(1,num+1) if num%n==0]
print(yaksu)
def yaksu( num ):
    return [ n for n in range(1,num+1) if num%n==0]






































































