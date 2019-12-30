from statistics import mean

class Student:
    def __init__(self, name, kor, eng, math, sum, ave):
        self.name = name
        self.kor = kor
        self.eng = eng
        self.math = math
        self.sum = sum
        self.ave = ave

    def print_info(self):
        print(self.name, '\t', self.kor, '\t', self.eng, '\t', self.math, '\t', self.sum, '\t', self.ave)


def set_student():
    n = input("이름: ")
    k = int(input("국어: "))
    e = int(input("영어: "))
    m = int(input("수학: "))
    s = sum([k, e, m])
    a = s/3
    return Student(n, k, e, m, s, a)


def find_student(data):
    n = input('검색할 이름을 입력하시오: ')
    f = 1
    for dt in data:
        if dt.name == n:
            print("----------------------------------------------")
            print("이름\t국어\t영어\t수학\t총점\t평균")
            dt.print_info()
            f = 0
    if f:
        print('Not found')


def print_all(data):
    for n in data:
        n.print_info()


def menu():
    print("1. 입력")
    print("2. 출력")
    print("3. 검색")
    print("4. 종료")
    n = int(input("번호를 입력하세요:"))
    return n


def run():
    data = []
    while 1:
        n = menu()
        if n == 1:
            while 1:
                data.append(set_student())
                s = input("계속 입력하시겠습니까(y/n)?")
                if s == 'n' or s == 'N':
                    break
        elif n == 2:
            print("----------------------------------------------")
            print("이름\t국어\t영어\t수학\t총점\t평균")
            print("----------------------------------------------")
            print_all(data)
            print("----------------------------------------------")
        elif n == 3:
            find_student(data)
        elif n == 4:
            break
        else:
            print("Wrong input!, retry.")
            continue


if __name__ == '__main__':
    run()

