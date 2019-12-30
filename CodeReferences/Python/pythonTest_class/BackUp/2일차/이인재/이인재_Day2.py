data_set=[]
def InputData():
    while True:
        name = input('이름:')
        kor = int(input('국어:'))
        english = int(input('영어:'))
        math = int(input('수학:'))
        data_set.append((name,kor,english,math))
        answer=input('계속 입력하시겠습니까 (y/n)?')
        if answer == 'n':
            breakmnn

def DisplayDataSet():
    print('----------------------------------------------')
    print("이름\t\t국어\t영어\t수학\t")
    print('----------------------------------------------')
    for a,b,c,d in data_set:
        print("%s\t\t%d\t\t%d\t\t%d"%(a,b,c,d))

    print('----------------------------------------------')

InputData()
DisplayDataSet()