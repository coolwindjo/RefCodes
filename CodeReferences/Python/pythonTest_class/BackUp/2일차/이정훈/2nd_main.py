import student


class TestClass():
    st = []

    def printMenu():
        print('1. 입력\n'
              '2. 출력\n'
              '3. 검색\n'
              '4. 종료\n'
              )

    def func_input():
        print ('func_input')
        name = input('이름 : ')
        kor = input('국어 : ')
        eng = input('영어 : ')
        math = input('수학 : ')
        TestClass.st.append(student.Student(name, kor, eng, math))

        cont = input('계속 입력하시겠습니까(y/n)? ')
        if cont == 'y':
            func_input()


    def func_display():
        print ('func_display')
        TestClass.base_display()
        for n in TestClass.st:
            print (n.getName(), n.getKor(), n.getEng(), n.getMath())

    def base_display():
        print(
              '----------------------------------------------------------------\n'
              '이름        국어        영어	수학	총점	평균\n'
              '----------------------------------------------------------------\n'
              )



    def func_search(name):
        print ('func_search')
        for n in TestClass.st:
            if n.getName() == name:
                TestClass.base_display()
                print (n.getName(), n.getKor(), n.getEng(), n.getMath())



def deffn():
    print ('invalid inputData')


obj = TestClass()
#menu = {1:TestClass.func_input, 2:TestClass.func_display, 3:TestClass.func_search}
inputData = 0

while inputData != 4:
    TestClass.printMenu()
    inputData = input('번호를 입력하세요 : ')
    inputData = int(inputData)

    if inputData == 1:
        TestClass.func_input()

    elif inputData == 2:
        TestClass.func_display()

    elif inputData == 3:

        TestClass.func_search(input('이름을 입력하세요 : '))

    elif inputData == 4:
        print('종료합니다.')
        break

    else:
        print('invalid inputData')






