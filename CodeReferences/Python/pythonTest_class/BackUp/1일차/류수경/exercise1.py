import math

# 1. 반지름과 높이를 입력받아 다음을 구하시요
# 1) 원기둥의 부피
# 2) 원뿔의 부피
def cal():
    r= int(input("반지름은? "))
    h= int(input("높이는? "))
    print("원기둥의 부피는 ",r**2*3.14*h)
    print("원뿔의 부피는 ",(r**2*3.14*h)/3)
#cal()

# 2. 하나의 도를 입력받아 화씨값을 구하시요
def temperature():
    temp= float(input("섭씨 온도 몇도? "))
    print("화씨값은 ", temp*1.8 +32)
#temperature()

# 3. cm 를 입력받아 인치를 구하시요
def cmtoin():
    n= float(input("몇 cm? "))
    print("인치in 는 ", n*0.393701)
#cmtoin()

# 4. km 를 입력받아 마일을 구하시요
def kmtomile():
    km= float(input("몇 km? "))
    print(km*0.621371," mile 입니다.")
#kmtomile()

# 5. 2개의 정수를 입력받아 절대값의 합을 구하시요
def sum():
    n1= int(input("정수1 입력하세요: "))
    n2= int(input("정수2 입력하세요: "))
    print("절대값의 합은 ", math.fabs(n1)+math.fabs(n2))
#sum()

# 6. 생년을 입력받아 나이를 출력하시요(현재년도 2018년을 기준)
def yourAge():
    birth= int(input("몇년도에 태어났습니까? : "))
    print("당신의 나이는 ", 2018-birth+1)
#yourAge()

# 7. 3개의 정수를 입력받아 가장큰값을 구하시요. --------------
def compare():
    n1= int(input("정수1 입력하세요: "))
    n2= int(input("정수2 입력하세요: "))
    n3= int(input("정수3 입력하세요: "))
    print("셋중 가장 큰값은 ", math)
#compare()

# 8. 년도를 입력받아 띠를 구하시요 ( 2018년은 개띠)
def yourYear():
    birth= int(input("몇년도에 태어났습니까? : "))
    if birth%12 == 0:
        rst= "원숭이띠"
    elif birth%12 == 2:
        rst = "닭띠"
    elif birth%12 == 2:
        rst = "개띠"
    elif birth%12 == 3:
        rst = "돼지띠"
    elif birth%12 == 4:
        rst = "쥐띠"
    elif birth%12 == 5:
        rst = "소띠"
    elif birth%12 == 6:
        rst = "호랑이띠"
    elif birth%12 == 7:
        rst = "토끼띠"
    elif birth%12 == 8:
        rst = "용띠"
    elif birth%12 == 9:
        rst = "뱀띠"
    elif birth%12 == 10:
        rst = "말띠"
    elif birth%12 == 11:
        rst = "양띠"
    else:
        rst="에러"
    print("당신의 띠는 ", rst)
#yourYear()

# 9. 년도를 입력받아 윤년 여부를 출력하시요 ----------------
# (윤년의 조건 4로 나눠 떨어지지만 100으로 나눠 떨어지면 않됨 또는 400으로 나눠 떨어짐 )
def yunYear():
    year= int(input("년도를 입력하세요 : "))
    if year%4 == 0 & year%100 != 0:
        print("입력하신 년도는 윤년입니다")
    else:
        print("입력하신 년도는 윤년이 아닙니다")
#yunYear()

# 10. 하나의 점수를 읽어 90~100 'A' 80~89 'B' 70~79 'C' 60~69 'D' 나머지 'F'
# 를 딕셔너리를 이용하여 작성하시요
def grade():
    dict = {range(90,101):'A',range(80,90):'B',range(70,80):'C',
            range(60,70):'D', range(0,60):'F'}
    score= int(input("점수를 입력하세요 : "))
    for keys in dict:
        if score in keys:
            print("등급은 ", dict.get(keys))
#grade()


# 11. salary=[1000,2000,3000,4000,5000 ] 의 연봉데이터가 있을때 세금 3.3을 제한
# 실수령액을 제너레이터를 이용하여 작성하시요
def calSalary():
    salary=[1000,2000,3000,4000,5000]
    sil = (n*(1-0.033) for n in salary)
    print(sil, type(sil))
    print(next(sil))
    print(next(sil))
    print(next(sil))
    print(next(sil))
    print(next(sil))
#calSalary()

# 12. 상품가격과 지불액을 입력하여 거스름돈의 갯수를 최소화하도록 거스름돈을 출력하시요
# (거스름돈, 500, 100, 50, 10 원 4가지종류로 한다 )
# 예) 상품가격 2160원 지불액 3000원이면 500원 1개, 100원 3개 50원1개 10원1개 로출력


# 13. 하나의 정수를 입력받아 해당정수의 약수를 구하시요.
def yak():
    n = int(input("하나의 정수를 입력하세요 : "))
    print("약수는 ", math)
#yak()
