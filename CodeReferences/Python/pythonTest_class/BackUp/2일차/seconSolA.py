from statistics import mean
data =[]
def inputData():
    while True:
        name = input('이름:')
        kor = int( input('국어:') )
        eng = int( input('영어:') )
        math = int( input('수학:') )
        data.append( (name, kor, eng, math) )
        yn = input('계속 입력하시겠습니까(y/n)?')
        if yn=='n':
            break
def outputData():
    print("="*30)
    print('{}\t{}\t{}\t{}\t{}\t{}'.format( '이름',
                    '국어','영어','수학','총점','평균' ) )
    print("="*30)
    for dt in data:
        tot = sum( dt[1:] )
        avg = mean( dt[1:] )
        print( '{0}\t{1}\t\t{2}\t\t{3}'.format( *dt ),
               tot,avg, sep='\t\t')
    ktot = sum( [ n[1] for n in data] )
    etot = sum( [ n[2] for n in data] )
    mtot = sum( [ n[3] for n in data] )
    kmean = mean( [ n[1] for n in data] )
    emean = mean( [ n[2] for n in data] )
    mmean = mean( [ n[3] for n in data] )
    kmax = max( data, key=lambda v:v[1])[1]
    emax = max( data, key=lambda v:v[2])[2]
    mmax = max( data, key=lambda v:v[3])[3]
    print("총점:","국어:", ktot,'영어:', etot,'수학:',mtot )
    print("평균:","국어:", kmean,'영어:', emean,'수학:',mmean )
    print("최고점수:","국어:", kmax,'영어:', emax,'수학:',mmax )


def searchData():
    sName = input('검색할 이름을 입력하세요:')
    f = filter(lambda v:v[0]==sName,data )
    #sData= [n for n in data if n[0]==sName]
    print("="*30)
    print('{}\t{}\t{}\t{}'.format( '이름',
                    '국어','영어','수학' ) )
    print("="*30)
    for dt in f:
        print( '{0}\t{1}\t{2}\t{3}'.format( *dt ) )



menu = {1:inputData, 2:outputData,3:searchData,4:exit}
while True:
    print('1.입력','2.출력','3.검색','4.종료',sep='\n')
    nSel = int( input('번호를 입력하세요:') )
    menu[nSel]()













