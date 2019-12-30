from dbHandle import *
def inputData():
    while True:
        name = input('이름:')
        kor = int( input('국어:') )
        eng = int( input('영어:') )
        insertTable(name,kor,eng)
        yn = input("계속입력(y/n):")
        if yn=='n':
            break
def outputData():
    for n,k,e in selectTable():
        print(n,k,e)
