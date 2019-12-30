import statistics

# 성적을 입력받아 결과를 출력하시요
# (함수로 구성하고 별도 모듈파일을 만드시요)

# global variable
jumsu=[]

# 입력)
# 1. 입력
# 이름:
# 국어:
# 영어:
# 수학:
# 계속 입력하시겠습니까(y/n)?
# 입력이 종료되면 메인메뉴로
def inputData():
    print('\n1. 입력\n')

    while True:
        name = input('이름:')
        kor = int(input('국어:') )
        eng = int(input('영어:') )
        math = int(input('수학:') )

        jumsu.append( {'name':name,'kor':kor,'eng':eng, 'math':math} )
        # print(jumsu)
        if input('계속입력(y/n):') == 'n':
            print('\n')
            break

# 2.출력
# -----------------------------------------------------------------
#     이름        국어        영어	수학	총점	평균
# ----------------------------------------------------------------
#      ㅁㅁㅁ      20        30	40
# 	...
# ----------------------------------------------------------------
# 총점: 국어 xx  영어 xx 수학
# 평균: 국어 xx  영어 xx 수학
# 최고점수: 국어 xx  영어 xx 수학

def outputResult():
    print('\n2. 출력')
    print('-----------------------------------------')
    print('이름\t','국어\t','영어\t','수학\t')
    print('-----------------------------------------')

    for n in jumsu:
        # print(n)
        # s1 = '이름:{name} 나이:{age}'.format(**d) # dictionary unpacking
        print( '{name} \t{kor} \t{eng} \t{math}'.format( **n) )

# print(sum([n[0] for n in data2]))
    kor_total = sum( [ n['kor'] for n in jumsu])
    eng_total = sum( [ n['eng'] for n in jumsu])
    math_total = sum( [ n['math'] for n in jumsu])
    print("총점: 국어", kor_total,'영어',eng_total,'수학',math_total)

# print(statistics.mean(data1))
# print(sum([n[0] for n in data2]))
#     print(statistics.mean(n['kor'] for n in jumsu))
    kor_average = statistics.mean(n['kor'] for n in jumsu)
    eng_average = statistics.mean(n['eng'] for n in jumsu)
    math_average = statistics.mean(n['math'] for n in jumsu)
    print("평균: 국어", kor_average,'영어',eng_average,'수학',math_average)

# print(max(data3, key=lambda v:v['kor'])['kor'])
    kor_max = max(jumsu, key=lambda v:v['kor'])['kor']
    eng_max = max(jumsu, key=lambda v:v['eng'])['eng']
    math_max = max(jumsu, key=lambda v:v['math'])['math']

    print("최고점수: 국어", kor_max,'영어',eng_max,'수학',math_max)
    print('\n')

# 3.검색
# 검색할 이름을 입력하세요:
# ----------------------------------------
#     이름        국어        영어	수학
# ----------------------------------------

def findData():
    Name2find = input('검색할 이름을 입력하세요:')

#filter : function, iterable functon에 해당하는 부분을 lambda ==> output은 generator => list로 형변환
# f = filter(lambda v:v>=20, data1)

    foundData = filter(lambda v:v['name'] == Name2find, jumsu)
    print('\n3. 검색')
    print('-----------------------------------------')
    print('이름\t','국어\t','영어\t','수학\t')
    print('-----------------------------------------')
    for n in foundData:
        print( '{name} \t{kor} \t{eng} \t{math}'.format( **n) )
    print('\n')

def terminate():
    print('종료합니다.')
    exit()

# (함수로 구성하고 ) - switch() -> dictionary 형태로
# 메인 메뉴)
#      1.입력
#      2.출력
#      3.검색
#      4.종료
#      번호를 입력하세요:

def defaultFn():
    print('1~4를 선택하세요\n')
#
# menu = {1:afn, 2:bfn}
# menu.get(1, defaultFn)()
menu= {1:inputData, 2:outputResult, 3:findData, 4:terminate }
while True:
    print('메인 메뉴)')
    print('\t1.입력')
    print('\t2.출력')
    print('\t3.검색')
    print('\t4.종료')
    print('\t번호를 입력하세요:')
    nItem = int( input() )
    menu.get(nItem, defaultFn)()
