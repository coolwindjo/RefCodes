#1. 반지름과 높이를 입력받아 다음을 구하시요
#1) 원기둥의 부피
#2) 원뿔의 부피

r = float(input('반지름의 길이 입력:'))
h = float(input('높이 입력:'))
volume1 = r**2*3.14*h
volume2 = r**2*3.14*h/3
s11 = '반지름 %f, 높이 %f인 원기둥의 부피 = %f'%(r,h,volume1)
s12 = '반지름 %f, 높이 %f인 원뿔의 부피 = %f'%(r,h,volume2)
print(s11)
print(s12)

# 2. 하나의 도를 입력받아 화씨값을 구하시요
# (섭씨온도 × 1.8) + 32 = 화씨온
temp = float(input('섭씨 온도 입력:'))
f = (temp*1.8)+32
s2 = '섭씨%f도 = %f 화씨' %(temp,f)
print(s2)

#3. cm 를 입력받아 인치를 구하시요
cm = float(input('cm 길이 입력:'))
inches = cm / 2.54
s3 = '%f cm = %f inch' %(cm,inches)
print(s3)

#4. km 를 입력받아 마일을 구하시요
km = float(input('km 입력:'))
mile = km/1.609
s4 = '%f km = %f mile' %(km,mile)
print(s4)

#5. 2개의 정수를 입력받아 절대값의 합을 구하시요
decimal1 = int(input('정수1 입력:'))
decimal2 = int(input('정수2 입력:'))
abs_hap = abs(decimal1)+abs(decimal2)
s5 = '%d와 %d의 절대값의 합은 %d' %(decimal1, decimal2,abs_hap)
print(s5)

#6. 생년을 입력받아 나이를 출력하시요(현재년도 2018년을 기준)
year = int(input('태어난해를 입력:'))
if year <= 0:
 print('wrong input')
else :
 age = 2019 - year + 1
 print('your age is', age)

#7. 3개의 정수를 입력받아 가장큰값을 구하시요.
decimal_1 = int(input('정수1 입력:'))
decimal_2 = int(input('정수2 입력:'))
decimal_3 = int(input('정수3 입력:'))

if decimal_1 >= decimal_2:
 if decimal_1 >= decimal_3:
  biggest_decimal = decimal_1
 else:
  biggest_decimal = decimal_3
else:
 if decimal_2 >= decimal_3:
  biggest_decimal = decimal_2
 else:
  biggest_decimal = decimal_3

s7 = '가장 큰 정수는 %d이다' %(biggest_decimal)
print(s7)

# 9. 년도를 입력받아 윤년 여부를 출력하시요
# (윤년의 조건 4로 나눠 떨어지지만 100으로 나눠 떨어지면 않됨 또는 400으로 나눠 떨어짐 )
year = int(input('해를 입력:'))

if year%400==0:
 s9 = '%d년은 윤년' %(year)
elif year%4==0 and year%100==0:
 s9 = '%d년은 윤년이 아니다' %(year)
elif year%4==0 and year%100!=0:
 s9 = '%d년은 윤년' %(year)
else:
 s9 = '%d년은 윤년이 아님' %(year)

print(s9)


#10 하나의 점수를 읽어 90~100 'A' 80~89 'B' 70~79 'C' 60~69 'D' 나머지 'F'
# 를 딕셔너리를 이용하여 작성하시요

#11. salary=[1000,2000,3000,4000,5000 ] 의 연봉데이터가 있을때 세금 3.3을 제한
#실수령액을 제너레이터를 이용하여 작성하시요
sil = [(1-0.033)*n*1000 for n in range(1,6) ]
print(sil)

# 12. 상품가격과 지불액을 입력하여 거스름돈의 갯수를 최소화하도록 거스름돈을 출력하시요
# (거스름돈, 500, 100, 50, 10 원 4가지종류로 한다 )
# 예) 상품가격 2160원 지불액 3000원이면 500원 1개, 100원 3개 50원1개 10원1개 로출력
price = int(input('상품가격 입력:'))
cost = int(input('지불액 입력:'))
num_500 = 0

if cost < price:
 print('지불금액 부족',(price-cost))
else:
 num_500 = (cost-price)/500
 num_100 = (cost-price-500*num_500)/100
 num_50 = (cost-price-500*num_500-100*num_100)/50
 num_10 = (cost-price-500*num_500-100*num_100-50*num_50)/10
 s12 = '거스름돈은 500원 동전 %d, 100원 동전 %d, 50원 동전 %d, 10원 동전 %d' %(num_500,num_100,num_50, num_10)
 print(s12)

# 13. 하나의 정수를 입력받아 해당정수의 약수를 구하시요.
decimal = int(input('약수 확인을 위한 정수 입력:'))
for n in range(1,decimal):
 if(decimal%n==0):
  print(n)
