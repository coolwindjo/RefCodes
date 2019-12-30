# -*- coding: utf-8 -*- 

class DayNameCalculator(object):

    # Class variables.
    _year_month_days = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    _day_names = ["Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"]
    
    @classmethod
    def input_date(cls):
        year = int(input("Enter the year: "))
        month = int(input("Enter the month:"))
        day = int(input("Enter the day:"))

        return year, month, day

    @classmethod    
    def _is_leap(cls, year):
        if year % 400 == 0:
            return True
        elif year % 100 == 0:
            return False
        elif year % 4 == 0:
            return True
        else:
            return False

    @classmethod
    def calculate(cls, year, month, day):
        total_days = 0

        for item in range(1, year):
            if cls._is_leap(item):
                total_days = total_days + 366
            else:
                total_days = total_days + 365

        for item in range(1, month):
            total_days = total_days + cls._year_month_days[item]

        if month >= 3:
            if cls._is_leap(year):
                total_days = total_days + 1
        
        total_days += day
        
        remainder = total_days % 7

        return(cls._day_names[remainder])


if __name__ == "__main__":
    year, month, day = DayNameCalculator.input_date()
    day_name = DayNameCalculator.calculate(year, month, day)
    print(day_name)
