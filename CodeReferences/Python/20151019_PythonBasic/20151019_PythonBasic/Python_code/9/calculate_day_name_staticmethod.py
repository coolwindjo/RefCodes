
class DayNameCalculator(object):

    _year_month_days = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    _day_names = ["일요일", "월요일", "화요일", "수요일", "목요일", "금요일", "토요일"]

    @staticmethod
    def input_date():
        year = int(input("년도를 입력하시오: "))
        month = int(input("월을 입력하시오: "))
        day = int(input("일을 입력하시오: "))

        return year, month, day

    @staticmethod    
    def _is_leap(year):
        if year % 400 == 0:
            return True
        elif year % 100 == 0:
            return False
        elif year % 4 == 0:
            return True
        else:
            return False

    @staticmethod
    def calculate(year, month, day):
        total_days = 0

        for item in range(1, year):
            if DayNameCalculator._is_leap(item):
                total_days = total_days + 366
            else:
                total_days = total_days + 365

        for item in range(1, month):
            total_days = total_days + DayNameCalculator._year_month_days[item]

        if month >= 3:
            if DayNameCalculator._is_leap(year):
                total_days = total_days + 1
        
        total_days += day
        
        remainder = total_days % 7

        return(DayNameCalculator._day_names[remainder])


if __name__ == "__main__":
    year, month, day = DayNameCalculator.input_date()
    day_name = DayNameCalculator.calculate(year, month, day)
    print(day_name)
