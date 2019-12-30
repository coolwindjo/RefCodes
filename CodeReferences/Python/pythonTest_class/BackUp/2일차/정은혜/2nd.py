##2일차 과제 (정은혜)


# 이름:
# 국어:
# 영어:
# 수학:
# 계속 입력하시겠습니까(y/n)?
# 입력이 종료되면 메인메뉴로
#
# ----------------------------------------------
#     이름        국어        영어		수학
# ----------------------------------------------
#      ㅁㅁㅁ      20          30		40
# 	...
# -----------------------------------------------

data =[]

def Append():
    Name = input('이름:')
    Kor = input('국어:')
    Eng = input('영어:')
    Math = input('수학:')
    data.append((Name,Kor,Eng,Math))


Append()
go = input('계속입력??(Y/N)')
while go == 'Y':
    Append()
    go = input('계속입력??(Y/N)')
else: print('no more input')

print('-----------------------')
print('이름   국어  영어  수학')
print('-----------------------')
for n in data:
    print('{}\t\t{}\t\t{}\t\t{}'.format(*n))



