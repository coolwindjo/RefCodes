class StudentScores(object):
    def __init__(self, data):
        self._data = data

    def __len__(self):
        return len(self._data)

    def __contains__(self, d):
        if d in self._data:
            return True
        else:
            return False

if __name__ == "__main__":
    student_scores = StudentScores([90, 95, 100])
    print(len(student_scores))
    print( 90 in student_scores)
    print( 80 in student_scores)

