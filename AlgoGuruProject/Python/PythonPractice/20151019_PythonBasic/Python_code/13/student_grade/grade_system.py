import os
import sys
from student import Student

class WrongStudentRecord(Exception):
    def __init__(self, message):
        self._message = message

class WrongFileName(Exception):
    def __init__(self, message):
        self._message = message

class StudentGradeSystem(object):

    def __init__(self, score_file):
        self._score_file = score_file

        if not os.path.isfile(self._score_file):
            raise WrongFileName("%s는 잘못된 파일 이름입니다." % self._score_file)

        self._students = []
        self._class_avg = 0.0
        self._kor_avg = 0.0
        self._eng_avg = 0.0
        self._math_avg = 0.0

        self._register_students()

    def _register_students(self):
        with open(self._score_file, "rt") as fp:
            lines = fp.readlines()

            for line in lines:
                items = (line.strip()).split(",")
        
                if len(items) != 5:
                    raise WrongStudentRecord("잘못된 성적 데이터가 있습니다.")
                num = items[0]
                name = items[1]

                try:
                    kor = int(items[2])
                    eng = int(items[3])
                    math = int(items[4])
                except:
                    raise WrongStudentRecord("성적에 숫자가 아닌 부분이 있습니다.")

                student = Student(num, name, kor, eng, math)
                self._students.append(student)


    def _calculate_student_order(self):
        temp_students = sorted(self._students, key = lambda x: x.total, reverse = True)

        order = 1
        for student in temp_students:
            student.order = order
            order = order + 1

        self._students = temp_students

    def _calculate_class_avg(self):
        total = 0

        for student in self._students:
            total = total + student.total

        self._class_avg = total / len(self._students)

    def _calculate_kor_avg(self):
        total = 0

        for student in self._students:
            total = total + student.kor

        self._kor_avg = total / len(self._students)

    def _calculate_eng_avg(self):
        total = 0

        for student in self._students:
            total = total + student.eng

        self._eng_avg = total / len(self._students)

    def _calculate_math_avg(self):
        total = 0

        for student in self._students:
            total = total + student.math

        self._math_avg = total / len(self._students)

    def _calculate_class_information(self):
        self._calculate_class_avg()
        self._calculate_kor_avg()
        self._calculate_eng_avg()
        self._calculate_math_avg()

    def process(self):
        self._calculate_student_order()
        self._calculate_class_information()

    def output_result(self, output_file):
        student_output_format = "번호: {:2}, 이름: {}, 국어: {}, 영어: {}, 수학: {}, 총점: {}, 평균: {:.2f}, 등수: {}\n"
        
        with open(output_file, "wt") as fp:
            for student in self._students:
                student_output = student_output_format.format(student.num, student.name, student.kor, student.eng,
                        student.math, student.total, student.avg, student.order)
                fp.write(student_output)
            
            fp.write("\n")
            fp.write("반 평균: %.2f\n" % self._class_avg)
            fp.write("국어 평균: %.2f\n" % self._kor_avg)
            fp.write("영어 평균: %.2f\n" % self._eng_avg)
            fp.write("수학 평균: %.2f\n" % self._math_avg)

        print("성적 처리가 끝났습니다.")


def main():
    try:
        student_grade_system = StudentGradeSystem(sys.argv[1])
        student_grade_system.process()
        student_grade_system.output_result(sys.argv[2])
    except WrongFileName as e:
        print(e.args[0])
        print("성적 처리 시스템이 비정상 종료합니다.")
    except WrongStudentRecord as e:
        print(e.args[0])
        print("성적 처리 시스템이 비정상 종료합니다.")
    else:
        print("성적 처리 시스템이 정상 종료합니다.")


if __name__ == "__main__":
    main()