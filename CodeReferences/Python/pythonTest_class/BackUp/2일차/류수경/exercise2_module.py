class Student:
    def __init__(self, name, kor, eng, math):
        self.name = name
        self.kor = kor
        self.eng = eng
        self.math = math
    def addScore(self, name, kor, eng, math):
        self.name = name
        self.kor = kor
        self.eng = eng
        self.math = math
    def show(self):
        print(self.name,self.kor,self.eng,self.math)

def main_menu():
      menu = {1:write, 2:read, 3:search, 4:close}
      num = int(input('(메인 메뉴)'
      '1.입력'   
      '2.출력'
      '3.검색'
      '4.종료'
      '번호를 입력하세요:'))
      menu[num]()

def write():
    name = input("이름: ")
    kor = input("국어: ")
    eng = input("영어: ")
    math = input("수학: ")

    s= Student(name,kor,eng,math)
    s.show()

    go = input("계속 입력하시겠습니까(y/n)? ")
    write() if go == 'y' else main_menu()

def read():
    pass

def search():
    pass

def close():
    pass

