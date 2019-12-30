import sys
#1. 반지름과 높이를 입력받아 다음을 구하시요
#1) 원기둥의 부피
#def cir1(x, y): # x = 반지름, y = 높이
#    return x*x*3.14*y
#2) 원뿔의 부피
#def cir2(x,y):
#    return (x*x*3.14*y)/3

#d = input('높이:')
#e = input('반지름:')
#print("원기둥: ", cir1(int(e), int(d)))
#print("원뿔: ", cir2(int(e), int(d)))

#2. 하나의 도를 입력받아 화씨값을 구하시요
#def ex2(x): # x = 반지름, y = 높이
#    return (x*1.8)+32
#e = input('섭씨:')
#print("화씨: ", ex2(int(e)))

#3. cm 를 입력받아 인치를 구하시요
#def ex3(x): # x = 반지름, y = 높이
#    return x*0.39
#e = input('cm:')
#print("inch: ", ex3(int(e)))

#4. km 를 입력받아 마일을 구하시요
#def ex4(x): # x = 반지름, y = 높이
#    return x*0.62
#e = input('km:')
#print("mile: ", ex4(int(e)))

#5. 2개의 정수를 입력받아 절대값의 합을 구하시요
#def ex5(x,y):
#    return abs(x)+abs(y)

#a = input('정수1')
#b = input('정수2')
#print("절대값: ", ex5(int(a), int(b)))

#6. 생년을 입력받아 나이를 출력하시요(현재년도 2018년을 기준)
#def ex6(x):
#    return 2018-x+1

#a = input('생년')
#print("나이: ", ex6(int(a)))

#7. 3개의 정수를 입력받아 가장큰값을 구하시요.
#def ex7(x,y,z):
#    if x > y and x > z:
#        return x
#    elif y > x and y > z:
#       return y
#    elif z > x and z > y:
#        return z

#a = input('')
#b = input('')
#c = input('')
#print("result: ", ex7(int(a),int(b),int(c)))

#8. 년도를 입력받아 띠를 구하시요 ( 2018년은 개띠)

#9. 년도를 입력받아 윤년 여부를 출력하시요
#(윤년의 조건 4로 나눠 떨어지지만 100으로 나눠 떨어지면 않됨 또는 400으로 나눠 떨어짐 )
#def ex9(x):
#    if (x%4 == 0) and (x%100 != 0):
#        print('윤년')
#    elif(x%400 == 0):
#        print('윤년')
#    else:
#        print('윤년 아님')

#a = input('생년')
#ex9(int(a))


#10. 하나의 점수를 읽어 90~100 'A' 80~89 'B' 70~79 'C' 60~69 'D' 나머지 'F'
#를 딕셔너리를 이용하여 작성하시요
#def ex10(x):
#    if (x < 101) and (x > 89):
#        print('A')
#    elif(x < 91) and (x > 79):
#        print('B')
#    elif(x < 81) and (x > 69):
#        print('C')
#    elif(x < 71) and (x > 59):
#        print('D')
#    else:
#        print('F')

#a = {'a':100,'b':90,'b':80}

#ex10(a.pop('a'))
#ex10(a.pop('b'))

#11. salary=[1000,2000,3000,4000,5000 ] 의 연봉데이터가 있을때 세금 3.3을 제한
#실수령액을 제너레이터를 이용하여 작성하시요
#def ex11(x):
#    return x - (x * 0.033)

#a = [1000,2000,3000,4000,5000]

#for n in range(len(a)):
#    print(ex11(a.pop()))

#12. 상품가격과 지불액을 입력하여 거스름돈의 갯수를 최소화하도록 거스름돈을 출력하시요
#(거스름돈, 500, 100, 50, 10 원 4가지종류로 한다 )
#예) 상품가격 2160원 지불액 3000원이면 500원 1개, 100원 3개 50원1개 10원1개 로출력
#def ex12(x):
#    if x >= 500:
#        y = x / 500
#        print('500원: ', int(y))
#        x = x - (int(y)*500)
#    if x >= 100:
#        y = x / 100
#        print('100원: ',int(y))
#        x = x - (int(y)*100)
#    if x >= 50:
#        y = x / 50
#        print('50원: ',int(y))
#        x = x - (int(y)*50)
#    if x >= 10:
#        y = x / 10
#        print('10원: ',int(y))
#        x = x - (int(y)*10)

#a = input('상품가격')
#ex12(int(a))



#13. 하나의 정수를 입력받아 해당정수의 약수를 구하시요.

def ex13(x)

