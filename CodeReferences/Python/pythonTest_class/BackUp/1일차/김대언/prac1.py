# 1. 반지름과 높이를 입력받아 다음을 구하시요
# 1) 원기둥의 부피
# 2) 원뿔의 부피


# def vol1(r, h):
#     return r**2*3.14*h
#
# def vol2(r, h):
#     return (vol1(r, h))/3
#
# print('원기둥/원뿔 부피 구하기')
# r, h = input('반지름과 높이를 순서대로 입력하세요. space로 값 구별').split()
# ret1 = vol1(float(r), float(h))
# ret2 = vol2(float(r), float(h))
# print(ret1)
# print(ret2)
# print('원기둥 : ' + str(ret1) + ' 원뿔 : ' + str(ret2))

# 2. 하나의 도를 입력받아 화씨값을 구하시요
#(0°C × 9/5) + 32 = 32°F
# print('2. 하나의 도를 입력받아 화씨값을 구하시요')
#
# def cnvtTemper(cel):
#     return (float(cel) * 9/5) + 32
#
# c = input('섭씨값을 입력하세요.')
#
# print(str(cnvtTemper(c)))


# 3. cm 를 입력받아 인치를 구하시요
# print('3. cm 를 입력받아 인치를 구하시요')
# cm = input('cm?')
# ret = float(cm) / 3.24
# print(str(ret) + ' inches')

# 4. km 를 입력받아 마일을 구하시요
# print('4. km 를 입력받아 마일을 구하시요')
# km = input('km?')
# ret = float(km) / 1.609
# print(str(ret) + ' miles')

# 5. 2개의 정수를 입력받아 절대값의 합을 구하시요
# print('5. 2개의 정수를 입력받아 절대값의 합을 구하시요')
# a, b = input('정수 2개 입력. 스페이스로 구별').split()
# def cal(x, y):
#     return abs(int(x)) + abs(int(y))
# print(str(cal(a, b)))

# 6. 생년을 입력받아 나이를 출력하시요(현재년도 2019년을 기준)
# print('6. 생년을 입력받아 나이를 출력하시요(현재년도 2019년을 기준)')
# by = int(input('생년?'))
# ny = 2019
# print(str(ny - by + 1) + '살 이시죠?')

# 7. 3개의 정수를 입력받아 가장큰값을 구하시요.
# print('7. 3개의 정수를 입력받아 가장큰값을 구하시요.')
# indexList = ['1', '2', '3']
# numList = list((input('정수 3개 입력. 스페이스로 구별').split()))
# myList = dict(zip(indexList, numList))
#
# def getMax(myDict):
#     retVal = None
#     for k, v in myDict.items():
#         val = int(v)
#         if (k == '1'):
#             retVal = val
#         else:
#             if (val > retVal):
#                 retVal = val
#
#     return retVal
#
# print(str(getMax(myList)))

# 8. 년도를 입력받아 띠를 구하시요 ( 2018년은 개띠)
# beltList = ['쥐', '소', '호랑이', '토끼', '용', '뱀', '말', '양', '원숭이', '닭', '개', '돼지']
# print('8. 년도를 입력받아 띠를 구하시요 ( 2019년은 돼지띠)')
# iy = int(input('년도?'))
# ry = (iy + 8) % 12
# print(beltList[ry])

# 9. 년도를 입력받아 윤년 여부를 출력하시요
# (윤년의 조건 4로 나눠 떨어지지만 100으로 나눠 떨어지면 않됨 또는 400으로 나눠 떨어짐 )
print('9. 년도를 입력받아 윤년 여부를 출력하시요')
iy = int(input('년도?'))
def checkYN(year):
    if year % 100 == 0:
        

print('')

# 10. 하나의 점수를 읽어 90~100 'A' 80~89 'B' 70~79 'C' 60~69 'D' 나머지 'F'
# 를 딕셔너리를 이용하여 작성하시요
print('10. 하나의 점수를 읽어 90~100 A 80~89 B 70~79 C 60~69 D 나머지 F')
print('')

# 11. salary=[1000,2000,3000,4000,5000 ] 의 연봉데이터가 있을때 세금 3.3을 제한
# 실수령액을 제너레이터를 이용하여 작성하시요
print('salary=[1000,2000,3000,4000,5000 ] 의 연봉데이터가 있을때 세금 3.3을 제한 실수령액을 제너레이터를 이용하여 작성하시요')
print('')

# 12. 상품가격과 지불액을 입력하여 거스름돈의 갯수를 최소화하도록 거스름돈을 출력하시요
# (거스름돈, 500, 100, 50, 10 원 4가지종류로 한다 )
# 예) 상품가격 2160원 지불액 3000원이면 500원 1개, 100원 3개 50원1개 10원1개 로출력
print('12. 상품가격과 지불액을 입력하여 거스름돈의 갯수를 최소화하도록 거스름돈을 출력하시요')
print('')

# 13. 하나의 정수를 입력받아 해당정수의 약수를 구하시요.
print('13. 하나의 정수를 입력받아 해당정수의 약수를 구하시요.')
print('')
