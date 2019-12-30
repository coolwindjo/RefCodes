

# print('===== 문제 1 =====')
# p1_r = int(input('반지름 입력:'))
# p1_h = int(input('높이 입력:'))
#
# p1_ans = 3.14*p1_r**2*p1_h
# print("원기둥의 부피 : ", p1_ans)
# print("원뿔의 부피 : ", p1_ans/3)
#
# print('===== 문제 2 =====')
# p2_celcious = int(input('섭씨온도 입력 :'))
# p2_ans = (p2_celcious*1.8)+32
# print(p2_ans)

# def prob3(cm):
#     return cm/2.54
#
# print('===== 문제 3 =====')
# p3_cm = float(input('센티미터 입력 :'))
# print(prob3(p3_cm))

# def prob4():
#     print('===== 문제 4 =====')
#     p4_km = float(input('킬로미터 입력 :'))
#     p4_mile = p4_km/1.6
#     print(p4_mile)
#
# prob4()

# print('===== 문제 5-1 =====')
# a = int(input('num1 : '))
# b = int(input('num2 : '))
# print(abs(a)+(abs(b)))

# print('===== 문제 5-2 =====')
# def prob5(n1, n2):
#     if n1 < 0:
#         n1 = -n1
#     if n2 < 0:
#         n2 = -n2
#     print(n1 + n2)
#
# p5_n1 = int(input('num1 : '));
# p5_n2 = int(input('num2 : '));
# prob5(p5_n1, p5_n2)

# print('===== 문제 6 =====')
# p6_born_age = int(input('생년? : '))
# p6_this_year = 2018
# print(p6_this_year-p6_born_age+2)

# def prob7(p7_tuple):
#     max_num = max(p7_tuple) # 라이브러리 문서를 보면max(arg1, arg2, *args[, key]) 을 세팅해야 한다는데 왜 tuple만 넣어놓아도 동작하는지 모르겠습니다...ㅠㅠ
#     print(max_num)
#
# print('===== 문제 7 =====')
# p7_tuple = (int(input('num1 : ')),int(input('num2 : ')), int(input('num3 : ')))
# prob7(p7_tuple)

# print('===== 문제 10 =====')
# def prob10(p10_score):
#     prob10_rank = {'A':90 <= p10_score}
#     print()

# prob10(int(input('num1 : ')))
a = 100
prob10_rank = {'A':90 <= a <= 100, 'B': 80 <= a < 89}
print(prob10_rank.get(80))
