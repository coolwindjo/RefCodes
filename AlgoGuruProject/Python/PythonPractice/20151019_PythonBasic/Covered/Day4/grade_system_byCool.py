from student_byCool import Student

class StudentGradeSystem(object):

    def __init__(self):
        self._students = []
        self._class_avg = 0.0
        self._kor_avg = 0.0
        self._eng_avg = 0.0
        self._math_avg = 0.0
        return

    def _calculate_student_order(self):
        temp_students = sorted(self._students, key = lambda x: x.total, reverse = True)
        order = 1
        for student in temp_students:
            student.order = order
            order += 1
        self._students = temp_students
        return

    def _calculate_class_avg(self):
        total = 0
        for student in self._students:
            total += student.total
        self._class_avg = total/len(self._students)
        return

    def _calculate_kor_avg(self):
        kor_total = 0
        for student in self._students:
            kor_total += student._kor
        self._kor_avg = kor_total/len(self._students)
        return

    def _calculate_eng_avg(self):
        eng_total = 0
        for student in self._students:
            eng_total += student._eng
        self._eng_avg = eng_total/len(self._students)
        return

    def _calculate_math_avg(self):
        math_total = 0
        for student in self._students:
            math_total += student._math
        self._math_avg = math_total/len(self._students)
        return

    def _calculate_class_information(self):
        self._calculate_class_avg()
        self._calculate_kor_avg()
        self._calculate_eng_avg()
        self._calculate_math_avg()
        return

    def register_student(self, student):
        self._students.append(student)
        return


    def process(self):
        #self._calculate_student_order()
        self._calculate_class_information()
        return

    def print_students(self):
        for student in self._students:
            print("번호: %s, 이름: %s, 국어: %d, 영어: %d, 수학: %d, 총점: %d, 평균: %.2f, 등수: %d"
                % (student.num, student.name, student.kor, student.eng, student.math, student.total, 
                   student.avg, student.order))
        return

    def print_class_information(self):
        print("반 평균: %.2f" % self._class_avg)
        print("국어 평균: %.2f" % self._kor_avg)
        print("영어 평균: %.2f" % self._eng_avg)
        print("수학 평균: %.2f" % self._math_avg)
        return

def main():
    student_grade_system = StudentGradeSystem()
    
    student = Student("1", "김민규", 90, 80, 85)
    student_grade_system.register_student(student)

    student = Student("2", "김용학", 90, 85, 90)
    student_grade_system.register_student(student)

    student = Student("3", "박영철", 80, 80, 80)
    student_grade_system.register_student(student)

    student_grade_system.process()
    student_grade_system.print_students()
    print()
    student_grade_system.print_class_information()

if __name__ == "__main__":
    main()
