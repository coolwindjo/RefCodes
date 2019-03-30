students = [{"num": "1", "name":"김민규", "kor": 90, "eng": 80, "math": 85, "total": 0.0, "order": 0},
            {"num": "2", "name":"김용학", "kor": 90, "eng": 85, "math": 90, "total": 0.0, "order": 0},
            {"num": "3", "name":"박영철", "kor": 80, "eng": 80, "math": 80, "total": 0.0, "order": 0}]

class_total = 0
class_avg = 0.0
kor_total = 0
kor_avg = 0.0
eng_total = 0
eng_avg = 0.0
math_total = 0
math_avg = 0.0

for student in students:
    student["total"] = student["kor"] + student["eng"] + student["math"]
    student["avg"] = student["total"] / 3
    class_total = class_total + student["total"]
    kor_total = kor_total + student["kor"]
    eng_total = eng_total + student["eng"]
    math_total = math_total + student["math"]

class_avg = class_total / len(students)
kor_avg = kor_total / len(students)
eng_avg = eng_total / len(students)
math_avg = math_total / len(students)

for student in students:
    print("번호: %s, 이름: %s, 국어: %d, 영어: %d, 수학: %d, 총점: %d, 평균:%.2f" 
          % (student["num"], student["name"], student["kor"], student["eng"], student["math"], 
          student["total"], student["avg"]))

print()

print("반 평균: %.2f" % class_avg)
print("국어 평균: %.2f" % kor_avg)
print("영어 평균: %.2f" % eng_avg)
print("수학 평균: %.2f" % math_avg)
