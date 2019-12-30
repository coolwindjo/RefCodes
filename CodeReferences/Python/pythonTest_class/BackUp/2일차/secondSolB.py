data =[]
def inputData():
    while True:
        name = input('이름:')
        kor = input('국어:')
        eng = input('영어:')
        math = input('수학:')
        data.append( (name, kor, eng, math) )
        yn = input('계속 입력하시겠습니까(y/n)?')
        if yn=='n':
            break
def outputData():
    print("="*30)
    print('{}\t{}\t{}\t{}'.format( '이름','국어','영어','수학' ) )
    print("="*30)
    for dt in data:
        print( '{}\t{}\t{}\t{}'.format( *dt ) )

inputData()
outputData()





