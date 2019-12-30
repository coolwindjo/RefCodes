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

    @property
    def num(self):
        return self._num

    @property
    def name(self):
        return self._name

    @property
    def kor(self):
        return self._kor

    @property
    def eng(self):
        return self._eng

    @property
    def math(self):
        return self._math

    @property
    def total(self):
        return self._total

    @property
    def avg(self):
        return self._avg

    @property
    def order(self):
        return self._order

    @order.setter
    def order(self, value):
        self._order = value

