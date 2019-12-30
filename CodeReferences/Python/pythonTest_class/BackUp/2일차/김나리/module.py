class Student():
    def __init__(self):
        self.name = 0
        self.korean = 0
        self.english = 0
        self.math = 0
        self.total = 0
        self.avg = 0

    def setName(self, x):
        self.name = x

    def setKorean(self,x):
        self.korean = x

    def setEnglish(self,x):
        self.english = x

    def setMath(self, x):
        self.math = x

    def calculate(self):
        self.total = self.korean + self.english + self.math
        self.avg = self.total / 3

    def show(self):
        print("%s   %d   %d   %d   %d   %.1f"%(self.name, self.korean, self.english, self.math, self.total, self.avg))

def main(data):
    print("1.입력")
    print("2.출력")
    print("3.검색")
    print("4.종료")
    menu = int(input("번호를 입력하세요: "))
    table = [inputData, outputData, searchData, terminate]

    if menu != 4:
        table[menu-1](data)
    else:
        table[menu-1]()

def inputData(data):
    name = input("이름: ")
    korean = int(input("국어: "))
    english = int(input("영어: "))
    math = int(input("수학: "))

    obj = Student()
    obj.setName(name)
    obj.setKorean(korean)
    obj.setEnglish(english)
    obj.setMath(math)
    obj.calculate()

    data.append(obj)

    cont = input("계속 입력하시겠습니까(y/n)? ")

    if cont == 'y':
        inputData(data)
    else:
        main(data)

def outputData(data):
    cnt = 0
    koreanTotal = 0
    englishTotal = 0
    mathTotal = 0
    koreanMax = 0
    englishMax = 0
    mathMax = 0

    print("-"*50)
    print("이름   국어   영어   수학   총점   평균")
    print("-"*50)
    for n in data:
        n.show()
        koreanTotal += n.korean
        englishTotal += n.english
        mathTotal += n.math
        cnt += 1
        koreanMax = n.korean if n.korean>koreanMax else koreanMax
        englishMax = n.english if n.english>englishMax else englishMax
        mathMax = n.math if n.math>mathMax else mathMax

    print("총점: 국어 %d 영어 %d 수학 %d"%(koreanTotal, englishTotal, mathTotal))
    print("평균: 국어 %.1f 영어 %.1f 수학 %.1f"%(koreanTotal/cnt, englishTotal/cnt, mathTotal/cnt))
    print("최고점수: 국어 %d 영어 %d 수학 %d"%(koreanMax, englishMax, mathMax))

    main(data)

def searchData(data):
    searchName = input("검색할 이름을 입력하세요: ")
    print("-"*50)
    print("이름   국어   영어   수학   총점   평균")
    print("-"*50)

    for n in data:
        if n.name == searchName:
            n.show()

    main(data)

def terminate():
    print("종료합니다.")
    exit()
