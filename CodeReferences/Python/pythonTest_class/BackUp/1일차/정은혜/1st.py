#정은혜 1일차 과제

# 1.반지름과 높이를 입력받아 다음을 구하시요
def shape(r,h):
    return print(r**2*3.14*h)
def shape2(r,h):
    return print(r**2*3.14*h/3)
r =input( '반지름:')
h =input( '높이:')
print('원기둥부피=')
shape(int(r),int(h))
print('원뿔부피=')
shape2(int(r),int(h))

# 2.하나의 도를 입력받아 화씨값을 구하시요
# 공식 : (3°C × 9/5) + 32 = 37.4°F
def func2(x):
    return print(x*9/5+32)
a= input('섭씨온도 입력:')
print('화씨온도 :')
func2(int(a))

# 3. cm 를 입력받아 인치를 구하시요
def func3(x):
    return print(x/2.54)
a= input('cm 입력:')
print('inch 출력 :')
func3(int(a))



#4. km 를 입력받아 마일을 구하시요
def func4(x):
    return print(x/1.609)
a= input('km 입력:')
print('mile 출력 :')
func4(int(a))


# 5. 2개의 정수를 입력받아 절대값의 합을 구하시요
def func5(a,b):
    result = abs(a) + abs(b)
    return print(result)

a = input('첫번째 정수입력:')
b = input('두번째 정수입력:')
print('결과는:')
func5(int(a),int(b))

#6. 생년을 입력받아 나이를 출력하시요(현재년도 2019년을 기준)
def func6(a):
    result = 2019-a+1
    return print(result)
age = input('생년입력:')
func6(int(age))

#7. 3개의 정수를 입력받아 가장큰값을 구하시요.
def func7(a,b,c):
    if a>=b and a>=c:
        result = a
    elif b>=c and b>=a:
        result = b
    else: result =c
    return print(result)

a = input('1번째 정수입력:')
b = input('2번째 정수입력:')
c = input('3번째 정수입력:')
print('가장 큰값은:')
func7(int(a),int(b),int(c))


#8. 년도를 입력받아 띠를 구하시요 ( 2019년은 돼지띠)
list = ['쥐', '소','호랑이','토끼','용','뱀','말','양','원숭이','닭','개','돼지']



