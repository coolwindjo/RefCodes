class Student(object):
    
    def __init__(self, num, name, kor, eng, math):
        self._num = num
        self._name = name
        self._kor = kor
        self._eng = eng
        self._math = math

        self._total = 0
        self._avg = 0.0
        self._order = 0

        self._calculate_total()
        self._calculate_avg()

    def _calculate_total(self):
        self._total = self._kor + self._eng + self._math

    def _calculate_avg(self):
        self._avg = self._total / 3

    def get_num(self):
        return self._num
    num = property(get_num)
    def get_name(self):
        return self._name
    name = property(get_name)
    def get_kor(self):
        return self._kor
    kor = property(get_kor)
    def get_eng(self):
        return self._eng
    eng = property(get_eng)
    def get_math(self):
        return self._math
    math = property(get_math)

    def get_total(self):
        return self._total
    total = property(get_total)
    def get_avg(self):
        return self._avg
    avg = property(get_avg)
    def get_order(self):
        return self._order
    def set_order(self, val):
        self._order=val
        return
    order = property(get_order,set_order)
