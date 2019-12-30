class Info:
    def __init__(self):
        self.name = ""
        self.kor = ""
        self.eng = ""
        self.math = ""
    def setData(self, name, kor, eng, math):
        self.name = name
        self.kor = kor
        self.eng = eng
        self.math = math
    def showData(self):
        print(self.name, "            "
              , self.kor,"            "
              , self.eng,"            "
              ,self.math)

menu = 0
info = Info()

while menu != 4:
    menu = input(" 1.입력\n 2.출력\n 3.검색\n 4.종료\n 번호를 입력하세요: ")
    if menu == '1':
        yn = 'y'
        while yn == 'y':
            name = input("이름: ")
            kor = input("국어: ")
            eng = input("영어: ")
            math = input("수학: ")
            info.setData(name, kor, eng, math)
            yn = input("계속 입력? (y/n) ")
            if yn == 'n':
                break
    elif menu == '2':
        print("------------------------------------------------------")
        print("    이름        국어        영어    	수학	총점	평균")
        info.showData()
    # yn = input("계속 입력? (y/n")
    # if yn == 'n':
    #     break


print(menu)