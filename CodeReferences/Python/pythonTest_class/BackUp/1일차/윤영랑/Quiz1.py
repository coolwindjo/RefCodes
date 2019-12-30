# 1. 반지름과 높이를 입력받아 다음을 구하시요
# 1) 원기둥의 부피
# 2) 원뿔의 부피
'''
print("1)")
r = int(input("반지름을 입력하시오:"))
h = int(input("높이를 입력하시오:"))
cylinder_volume = h*3.14*r**2
cone_volume = h*3.14*r**2/3
print(f"원기둥의 부피는 {cylinder_volume}입니다")
print(f"원뿔의 부피는 {cone_volume}입니다")


# 2. 하나의 도를 입력받아 화씨값을 구하시요
print("2)")
c = float(input("섭씨 온도를 입력하시오:"))
f = c*9/5+32
print(f"화씨 온도는 {f}입니다")

# 3. cm 를 입력받아 인치를 구하시요
print("3)")
cm = float(input("cm를 입력하시오:"))
inch = cm/2.54
print("%.3finch입니다"%inch)

# 4. km 를 입력받아 마일을 구하시요
print("4)")
km = float(input("km를 입력하시오:"))
mile = km*0.621371
print("%.4fmile입니다"%mile)


# 5. 2개의 정수를 입력받아 절대값의 합을 구하시요
print("5)")
n1 = int(input("첫번째 정수를 입력하시오:"))
n2 = int(input("두번째 정수를 입력하시오:"))
rst = abs(n1) + abs(n2)
print("두 정수의 절대값의 합은 ", rst, "입니다")


# 6. 생년을 입력받아 나이를 출력하시요(현재년도 2019년을 기준)
print("6)")
year = int(input("생년을 입력하시오:"))
print("2019년 현재 나이는 ", 2019-year+1,"입니다")


# 7. 3개의 정수를 입력받아 가장큰값을 구하시요.
print("7)")
n1 = int(input("첫번째 정수를 입력하시오:"))
n2 = int(input("두번째 정수를 입력하시오:"))
n3 = int(input("세번째 정수를 입력하시오:"))
print("세 정수 중 가장 큰 값은 ", max(n1, n2, n3),"입니다")


# 8. 년도를 입력받아 띠를 구하시요 ( 2019년은 돼지띠)
print("8)")
year = int(input("태어난 해를 입력하시오:"))
animals = ('원숭이', '닭', '개', '돼지', '쥐', '소', '호랑이', '토끼', '용', '뱀', '말', '양')
year_animal = animals[year%12]
print(f'{year}년은 {year_animal}띠입니다')


# 9. 년도를 입력받아 윤년 여부를 출력하시요
# (윤년의 조건 4로 나눠 떨어지지만 100으로 나눠 떨어지면 않됨 또는 400으로 나눠 떨어짐 )
print("9)")
year = int(input("년도를 입력하시오:"))
if year%4 is 0 and year%100 is not 0 or year%400 is 0:
    print(f'{year}년은 윤년입니다')
else:
    print(f'{year}년은 평년입니다')

# 10. 하나의 점수를 읽어 90~100 'A' 80~89 'B' 70~79 'C' 60~69 'D' 나머지 'F'
# 를 딕셔너리를 이용하여 작성하시요
print("10)")
score = int(input("점수를 입력하시오:"))
grade = {(90, 100):'A', (80, 89):'B', (70, 79):'C', (60, 69):'D'}
for k, v in grade.items():
    min, max = k
    if score >= min and score <= max:
        print (v, "학점입니다")
        break
else:
    print ("F학점입니다")


# 11. salary=[1000,2000,3000,4000,5000 ] 의 연봉데이터가 있을때 세금 3.3을 제한
# 실수령액을 제너레이터를 이용하여 작성하시요
print("11)")
salary = [n*1000 for n in range(1,6)]
print("연봉:", salary)
income = [s*(1-0.033) for s in salary]
print("실수령액:", salary)
'''

# 12. 상품가격과 지불액을 입력하여 거스름돈의 갯수를 최소화하도록 거스름돈을 출력하시요
# (거스름돈, 500, 100, 50, 10 원 4가지종류로 한다 )
# 예) 상품가격 2160원 지불액 3000원이면 500원 1개, 100원 3개 50원1개 10원1개 로출력
print("12)")
price = int(input("상품가격을 입력하시오:"))
cash = int(input("지불액을 입력하시오:"))
diff = cash - price
if (diff < 0):
    print("지불액이 부족합니다")

change_500 = diff//500
diff = diff%500
change_100 = diff//100
diff = diff%100
change_50 = diff//50
diff = diff%50
change_10 = diff//10

print ("거스름돈은 ", end='')
if change_500 > 0 :
    print (f'500원 {change_500}개', end=' ')
if change_100 > 0 :
    print (f'100원 {change_100}개', end=' ')
if change_50 > 0 :
    print (f'50원 {change_50}개', end=' ')
if change_10 > 0 :
    print (f'10원 {change_10}개', end=' ')

if change_10 == 0 and change_50 == 0 and change_100 == 0 and change_500 == 0:
    print("없습니다")
else:
    print("입니다")


# 13. 하나의 정수를 입력받아 해당정수의 약수를 구하시요.
number = int(input("약수를 구할 정수를 입력하시오:"))
measure = [n for n in range(1,number) if number%n==0]
print (measure)


