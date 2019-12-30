class Student:
    def setGrade(self, name, kor, eng, math):
        self.name = name
        self.kor = kor
        self.eng = eng
        self.math = math
        self.total = int(self.kor) + int(self.eng) + int(self.math)
        self.aver = float(self.total) / 3

    def show(self):
        # print('show id', id(self))
        print("---------------------------------------------------------------------")
        print("    이름        국어        영어        수학        총점        평균")
        print("---------------------------------------------------------------------")
        print("    %s         %d          %d          %d          %d          %d"%
              (self.name, self.kor, self.eng, self.math, self.total, self.aver))
        print("---------------------------------------------------------------------")


g = Student()
# while i == 'n':
while True:
    name = input('이름:')
    kor = int(input('국어:') )
    eng = int(input('영어:') )
    math = int(input('수학:') )

    g.setGrade(name, kor, eng, math)
    g.show()

    # print(jumsu)
    if input('계속입력????(y/n):') == 'n':
        print('\n')
        break
#
# print('이름:')
# name = str(input())
# print('국어:')
# age = int(input())
# print("영어:")
# eng = int(input())
# print("수학:")
# math = int(input())
# print("계속 입력하시겠습니까(y/n)? ")
# i = str(input())
# g.setGrade(name, age, eng, math)
# g.show()
