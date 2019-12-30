# day 1 quiz

def fn1():
    # 1. 반지름과 높이를 입력받아 다음을 구하시요
    # 1) 원기둥의 부피
    # 2) 원뿔의 부피
    print('========== 문제1 ==========')
    r = int(input('반지름:'))
    h = int(input('높이:'))

    V1 = 3.14*(r**2) * h        # 원기둥의 부피 = pi * r **2 * h
    V2 = 3.14*(r**2) * h / 3    # 원뿔의 부피 = pi * r * r * h / 3

    print('원기둥의 부피:%.2f' % V1)
    print('원뿔의 부피:%.2f' % V2)
    print('===========================')

def fn2():
    # 2. 하나의 도를 입력받아 화씨값을 구하시요
    print('========== 문제2 ==========')
    # (섭씨온도 × 1.8) + 32 = 화씨온도
    c = float(input('섭씨온도:'))
    f = (c * 1.8) + 32
    print('입력섭씨온도:%.2f, 변환된화씨온도:%.2f' % (c, f))
    print('===========================')

def fn3():
    # 3. cm 를 입력받아 인치를 구하시요
    print('========== 문제3 ==========')
    # inch = cm / 2.54
    cm = float(input('cm:'))
    inch = cm / 2.54
    print('입력cm:%.2f, 변환된inch:%.2f' % (cm, inch))
    print('===========================')

def fn4():
    # 4. km 를 입력받아 마일을 구하시요
    print('========== 문제4 ==========')
    # mile = km / 1.609
    km = float(input('km:'))
    mile = km / 1.609
    print('입력km:%.2f, 변환된mile:%.2f' % (km, mile))
    print('===========================')

def fn5():
    # 5. 2개의 정수를 입력받아 절대값의 합을 구하시요
    print('========== 문제5 ==========')
    i1 = int(input('정수1:'))
    i2 = int(input('정수2:'))
    rst = abs(i1+i2)
    print('절대합: |정수1+정수2| = %d' % rst)
    print('===========================')

def fn6():
    # 6. 생년을 입력받아 나이를 출력하시요(현재년도 2019년을 기준)
    print('========== 문제6 ==========')
    year = int(input('생년:'))
    age = 2019 - year
    print('2019년 현재 한국나이: %d' % (age+1))
    print('===========================')

def fn7():
    # 7. 3개의 정수를 입력받아 가장큰값을 구하시요.
    print('========== 문제7 ==========')
    i1 = int(input('정수1:'))
    i2 = int(input('정수2:'))
    i3 = int(input('정수3:'))
    max_int = max(i1,i2,i3)
    print('가장 큰 수: %d' % (max_int))
    print('===========================')

def fn8():
    # 8. 년도를 입력받아 띠를 구하시요 (2019년은 돼지띠)
    # 4:쥐(2008) 5:소(2009) 6:범(2010) 7:토(2011) 8:용(2012) 9:뱀(2013) 10:말(2014) 11:양(2015) 0:원(2016) 1:닭(2017) 2:개(2018) 3:돼(2019)
    print('========== 문제8 ==========')
    year_list = ['원숭이','닭','개','돼지','쥐','소','호랑이','토끼','용','뱀','말','양']
    year = int(input('년도:'))
    tti = int(year % 12)
    print('%d년도는 %s띠 입니다.' % (year,year_list[tti]))
    print('===========================')

def fn9():
    # 9. 년도를 입력받아 윤년 여부를 출력하시요
    # (윤년의 조건 4로 나눠 떨어지지만 100으로 나눠 떨어지면 않됨 또는 400으로 나눠 떨어짐 )
    print('========== 문제9 ==========')
    year = int(input('년도:'))
    is_true = (((year % 4) == 0) and ((year % 100) != 0)) or ((year % 400) == 0)
    if is_true:
        print('%d년도는 윤년 입니다.' % (year))
    else:
        print('%d년도는 윤년이 아닙니다.' % (year))
    print('===========================')

def fn10():
    # 10. 하나의 점수를 읽어 90~100 'A' 80~89 'B' 70~79 'C' 60~69 'D' 나머지 'F'
    # 를 딕셔너리를 이용하여 작성하시요
    print('========== 문제10 ==========')
    score = int(input('점수:'))
    if score>=90:
        print('A')
    elif score>=80:
        print('B')
    elif score>=70:
        print('C')
    elif score>=60:
        print('D')
    else:
        print('F')
    print('===========================')

def fn11():
    # 11. salary=[1000,2000,3000,4000,5000 ] 의 연봉데이터가 있을때 세금 3.3을 제한
    # 실수령액을 제너레이터를 이용하여 작성하시요
    print('========== 문제11 ==========')
    salary = [1000,2000,3000,4000,5000]
    sil = [n*0.967 for n in salary]
    print(sil)
    print('===========================')

def fn12():
    # 12. 상품가격과 지불액을 입력하여 거스름돈의 갯수를 최소화하도록 거스름돈을 출력하시요
    # (거스름돈, 500, 100, 50, 10 원 4가지종류로 한다 )
    # 예) 상품가격 2160원 지불액 3000원이면 500원 1개, 100원 3개 50원1개 10원1개 로출력
    print('========== 문제12 ==========')
    print('===========================')

def fn13():
    # 13. 하나의 정수를 입력받아 해당정수의 약수를 구하시요.
    print('========== 문제13 ==========')
    print('===========================')

# 실행결과
# fn1()
# fn2()
# fn3()
# fn4()
# fn5()
# fn6()
# fn7()
# fn8()
# fn9()
# fn10()
# fn11()
# fn12()
# fn13()


