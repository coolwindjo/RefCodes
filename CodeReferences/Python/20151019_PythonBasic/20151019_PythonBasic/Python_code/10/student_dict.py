class StudentDict(object):
    def __init__(self):
        self._data = {}

    def __getitem__(self, key):
        return self._data[key]

    def __setitem__(self, key, value):
        self._data[key] = value

    def __delitem__(self, key):
        if key in self._data:
            del self._data[key]
            print(key, "가 삭제되었습니다")
        else:
            print(key, "가 없습니다.")

if __name__ == "__main__":
    student_a = StudentDict()

    student_a["name"] = "Sam"
    print(student_a["name"])
    del student_a["name"]
