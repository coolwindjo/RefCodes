import homework_module as m



menuDic = {1:m.inputMenu,2:m.outputMenu,3:m.searchMenu}

def showMenu():
    print('1.입력')
    print('2.출력')
    print('3.검색')
    print('4.종료')

myDataList = list()
while True:
    showMenu()
    n = int(input('번호를 입력하세요:'))
    if n == 4:
        break
    else:
        menuDic.get(n)(myDataList)

