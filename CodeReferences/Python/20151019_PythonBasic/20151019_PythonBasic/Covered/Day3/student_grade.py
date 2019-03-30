def calculate_total(students):
    for student in students:
        student["total"] = student["kor"] + student["eng"] + student["math"]

def calculate_average(students):
    for student in students:
        student["avg"] = student["total"] / len(students)

def calculate_order(students):
    temp_students = sorted(students, key = lambda x: x["total"], reverse=True)
    order = 1
    for student in temp_students:
        student["order"] = order
        order = order + 1

    return temp_students

def calculate_class_avg(students):
    class_total = 0

    for student in students:
        class_total = class_total + student["total"]

    return class_total / len(students)

def calculate_kor_avg(students):
    kor_total = 0

    for student in students:
        kor_total = kor_total + student["kor"]

    return kor_total / len(students)

def calculate_eng_avg(students):
    eng_total = 0

    for student in students:
        eng_total = eng_total + student["eng"]

    return eng_total / len(students)

def calculate_math_avg(students):
    math_total = 0

    for student in students:
        math_total = math_total + student["math"]

    return math_total / len(students)

def print_student(students):
    for student in students:
        print("번호: %s, 이름: %s, 국어: %d, 영어: %d, 수학: %d, 총점: %d, 평균: %.2f, 등수: %d" 
        % (student["num"], student["name"], student["kor"], student["eng"], student["math"], 
        student["total"], student["avg"], student["order"]))

def print_class(class_avg, kor_avg, eng_avg, math_avg):
    print("반 평균: %.2f" % class_avg)
    print("국어 평균: %.2f" % kor_avg)
    print("영어 평균: %.2f" % eng_avg)
    print("수학 평균: %.2f" % math_avg)
    

def main():
    students = [{"num": "1", "name":"김민규", "kor": 90, "eng": 80, "math": 85, "total": 0.0, "order": 0},
            {"num": "2", "name":"김용학", "kor": 90, "eng": 85, "math": 90, "total": 0.0, "order": 0},
            {"num": "3", "name":"박영철", "kor": 80, "eng": 80, "math": 80, "total": 0.0, "order": 0}]

    class_avg = 0.0
    kor_avg = 0.0
    eng_avg = 0.0
    math_avg = 0.0

    calculate_total(students)
    calculate_average(students)
    students = calculate_order(students)
    
    class_avg = calculate_class_avg(students)
    kor_avg = calculate_kor_avg(students)
    eng_avg = calculate_eng_avg(students)
    math_avg = calculate_math_avg(students)
  
    print_student(students)
    print()
    print_class(class_avg, kor_avg, eng_avg, math_avg)

if __name__ == "__main__":
    main()
    

