class Subject:
    def __init__(self, Korean, English, Mathmetics):
        self.Korean = Korean
        self.English = English
        self.Mathmetics = Mathmetics

class Student(Subject):
    def __init__(self, name, Korean, English, Mathmetics):
        super().__init__(Korean, English, Mathmetics)
        self.name = name

    def show(self):
        print(self.name, self.Korean, self.English, self.Mathmetics)

while_loop = 'y'
student_score_data = []
while while_loop == 'y':
    student = str(input('이름 :'))
    kor = int(input('국어:'))
    eng = int(input('영어:'))
    mat = int(input('수학:'))
    student_score_data.append(Student(student, kor, eng, mat))

    while_loop = str(input('계속입력하시겠습니까? (y/n):'))
else :
    print('--------------------------------')
    print(' name   korean   english   math ')
    print('--------------------------------')
    for n in student_score_data:
        print(n.name,'\t', n.Korean, '\t\t',n.English, '\t\t',n.Mathmetics)
    print('--------------------------------')
