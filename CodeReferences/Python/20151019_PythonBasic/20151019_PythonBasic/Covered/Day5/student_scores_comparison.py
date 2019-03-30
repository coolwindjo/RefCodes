class StudentScores(object):
    def __init__(self, data):
        self._data = data
        self._total = sum(self._data)

    def __eq__(self, y):
        return self._total == y._total

    def __lt__(self, y):
        return self._total < y._total

    def __le__(self, y):
        return self._total <= y._total

if __name__ == "__main__":
    student_a = StudentScores([90, 95, 100])
    student_b = StudentScores([80, 85, 90])

    print( student_a == student_b)          # 1
    print( student_a < student_b)           # 2

