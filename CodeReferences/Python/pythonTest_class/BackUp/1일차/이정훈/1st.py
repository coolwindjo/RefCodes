# print('[1]==========================')
#
# inpR = input ('반지름 입력  : ')
# inpH = input ('높이 입력 : ')
# inpR = int(inpR)
# inpH = int(inpH)
#
# print ('원기둥 부피 : ', 3.14 * inpR**2 * inpH)
# print ('원뿔 부피 : ', (3.14 * inpR**2 * inpH) / 3)
#
# print('[2]==========================')
# inp_temp = input ('섭씨 입력 : ')
# print ('화씨 : ', float(inp_temp) * 9 / 5 + 32)
#
# print('[3]==========================')
# inp_temp = input ('cm 입력 : ')
# print ('인치 : ', float(inp_temp) * 0.393701)
#
# print('[4]==========================')
# inp_temp = input ('km 입력 : ')
# print ('마일 : ', float(inp_temp) * 0.621371)
#
# print('[5]==========================')
# a = input ('정수 a 입력 : ')
# b = input ('정수 b 입력 : ')
# print ('a,b 절대값의 합 : ', abs(int(a)) + abs(int(b)) )
#
# print('[6]==========================')
# a = input ('생년 입력 : ')
# print ('나이 : ', 2019- int(a) + 1)
#
# print('[7]==========================')
# a = input ('정수 a 입력 : ')
# b = input ('정수 b 입력 : ')
# c = input ('정수 c 입력 : ')
#
# a = int(a)
# b = int(b)
# c = int(c)
#
# if a > b:
#     if a > c:
#         d = a
#     else:
#         d = c
# elif b > c:
#     d = b
# else:
#     d = c
#
# print ('가장 큰 값 : ', d)
#
# print('[8]==========================')
# a = input ('생년 입력 : ')
# a = int(a)
#
# d = ['쥐','소','호랑이','토끼','용','뱀','말','양','원숭이','닭','개','돼지']
# e = enumerate(d)
# dic = dict(e)
#
# print ("((2019 - a) % 12) = ", ((2019 - a) % 12) )
# index = 11 - ((2019 - a) % 12)
#
# print ('띠 : ', dic[index])
#
# print('[9]==========================')
# a = input ('생년 입력 : ')
# a = int(a)
# b = False
#
# if a % 4 == 0 and a % 100 != 0:
#     b = True
#
# if a % 400 ==0:
#     b = True
#
# if b == True:
#     print ('윤년 입니다.')
# else:
#     print ('윤년이 아닙니다.')
#
# print('[10]=========================')
# a = input ('점수 입력 : ')
# a = int(a)
#
#
#
# print('[11]=========================')
# salalry = [ n*1000 for n in range(1,6)]
# salalry = [n*(1-0.033) for n in salalry]
# print ('실수령액 : ', salalry)
#
#
# print('[12]=========================')
# a = input ('상품가격 : ')
# b = input ('지불액 : ')
# a = int(a)
# b = int(b)
# c = b - a
#
# c_500 = c // 500
# c_100 = (c - (c_500 * 500)) // 100
# c_50 = (c - (c_500 * 500) - (c_100 * 100)) // 50
# c_10 = (c - (c_500 * 500) - (c_100 * 100) - (c_50 * 50)) // 10
#
# print ('500 : %d, 100 : %d, 50 : %d, 10 : %d,' %(c_500,c_100,c_50,c_10))
#
#
# print('[13]=========================')
