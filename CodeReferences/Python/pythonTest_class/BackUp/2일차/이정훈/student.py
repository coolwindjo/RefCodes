
class Student():
    def __init__(self, name, kor, eng, math):
    #def __init__(self):
        self.name = name
        self.kor = kor
        self.eng = eng
        self.math = math

    def getName(self):
        return self.name

    def getKor(self):
        return self.kor

    def getEng(self):
        return self.eng

    def getMath(self):
        return self.math

    def setName(self):
        self.name = input ('이름 : ')

    def setKor(self):
        self.kor = input ('국어 : ')

    def setEng(self):
        self.eng = input ('영어 : ')

    def setMath(self):
        self.math = input ('수학 : ')


