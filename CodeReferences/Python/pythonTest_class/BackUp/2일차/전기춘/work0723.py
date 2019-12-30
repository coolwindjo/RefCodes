class Student:
    def __init__(self, name, kor, eng, math):
        self.name = name
        self.kor = {"name": "한국", "value": kor}
        self.eng = {"name": "영어", "value": eng}
        self.math = {"name": "수학", "value": math}

        print(self.kor.get("value"))

    def getName(self):
        return self.name

    def print(self):
        print("    %s    %d    %d    %d"%(self.name, self.kor.get("value"), self.eng.get("value"), self.math.get("value")))

    def printMore(self):
        scoreSum = self.kor.get("value") + self.eng.get("value") + self.math.get("value")
        avgScore = scoreSum / 3

        maxScore = self.kor if self.kor.get("value") > self.eng.get("value") else self.eng
        maxScore = self.math if self.math.get("value") > maxScore.get("value") else maxScore

        print("    %s    %d    %d    %d    %d    %d    %s"%(self.name, self.kor.get("value"), self.eng.get("value"),
                                                                  self.math.get("value"), scoreSum, avgScore, maxScore.get("name")))

class System:
    def __init__(self):
        self.stuInfo = [Student("asdf", 50, 60, 70)]


    def _addInfo(self):
        print("1. 입력")
        name = input("이름: ")
        kor = int(input("국어: "))
        eng = int(input("영어: "))
        math = int(input("수학: "))

        self.stuInfo.append(Student(name, kor, eng, math))

        str = input("계속 입력하겠습니까?(y/n)")
        if str == "n":
            self.showMenu()
        elif str == "y":
            self._addInfo()

    def _searchInfo(self):
        name = input("검색할 이름을 입력하세요: ")
        print("-------------------------------------------------------")
        print("    이름    국어    영어    수학")
        print("-------------------------------------------------------")
        for n in self.stuInfo:
            if n.getName() == name:
                n.print()

        str = input("계속 검색하겠습니까?(y/n)")
        if str == "n":
            self.showMenu()
        elif str == "y":
            self._searchInfo()

    def _printInfo(self):
        print("-------------------------------------------------------")
        print("    이름    국어    영어    수학    총점    평균    최고점수    ")
        print("-------------------------------------------------------")

        for n in self.stuInfo:
            n.printMore()

        self.showMenu()

    def _exit(self):
        print("시스템 종료~~~")

    def showMenu(self):
        print("1. 입력")
        print("2. 출력")
        print("3. 검색")
        print("4. 종료")

        actions = {
            "1": self._addInfo,
            "2": self._printInfo,
            "3": self._searchInfo,
            "4": self._exit
        }
        index = input("번호를 입력하세요: ")

        actions[index]()


sys = System()
sys.showMenu()
