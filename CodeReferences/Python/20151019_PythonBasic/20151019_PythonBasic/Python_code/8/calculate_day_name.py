def input_date():
    year = int(input("년도를 입력하시오: "))
    month = int(input("월을 입력하시오: "))
    day = int(input("일을 입력하시오: "))

    return year, month, day

class DayName(object):

    def __init__(self, year, month, day):
        self._year = year
        self._month = month
        self._day = day
        self._name = None
        self._year_month_days = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
        self._day_names = ["일요일", "월요일", "화요일", "수요일", "목요일", "금요일", "토요일"]
        
        self._calculate_day_name()
        
    def _is_leap(self, year):
        if year % 400 == 0:
            return True
        elif year % 100 == 0:
            return False
        elif year % 4 == 0:
            return True
        else:
            return False

    def _calculate_day_name(self):
        total_days = 0

        for item in range(1, self._year):
            if self._is_leap(item):
                total_days = total_days + 366
            else:
                total_days = total_days + 365

        for item in range(1, self._month):
            total_days = total_days + self._year_month_days[item]

        if self._month >= 3:
            if self._is_leap(self._year):
                total_days = total_days + 1
        
        total_days += self._day
        
        remainder = total_days % 7

        self._name = self._day_names[remainder]

    def get_name(self):
        return self._name

if __name__ == "__main__":
    year, month, day = input_date()
    day_name = DayName(year, month, day)
    print(day_name.get_name())
