
class Student:
    def setData(self, name, kor, eng,math):
        self.name = name
        self.kor = kor
        self.eng = eng
        self.math = math

def inputUserData():
    stdName = input("이름:")
    stdKor = input("국어:")
    stdEng = input("영어:")
    stdMath = input("수학:")
    obj.setData(stdName, stdKor, stdEng, stdMath)

obj = Student()
continueFlag = "y"

while continueFlag == 'y':
    inputUserData()
    continueFlag = input("계속 입력하시겠습니까(y/n)?")

print("--------------------------------------------------")
print("이름\t\t 국어\t\t 영어 \t\t 수학 \t\t")
print("--------------------------------------------------")
print(obj.name, obj.kor, obj.eng, obj.math)
print("--------------------------------------------------")



