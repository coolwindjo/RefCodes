# 년월일을 입력받는 함수이다
# 반환값: 년월일을 튜플형태로 반환
def input_date():
    year = int(input("년도를 입력하시오: "))
    month = int(input("월을 입력하시오: "))
    day = int(input("일을 입력하시오: "))
    return year, month, day

# 윤년인지를 확인하는 함수이다.
# 입력인자: year: 년도
# 반환값: True: 윤년이다, False: 윤년이 아니다.
def is_leap(year):
    if year % 400 == 0:
        return True
    elif year % 100 == 0:
        return False
    elif year % 4 == 0:
        return True
    else:
        return False

# 요일을 구하는 함수이다.
# 입력인자: year: 년도, month: 월, day: 일
# 반환값: 요일
def get_day_name(year, month, day):

    total_days = 0

    year_month_days = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    day_names = ["일요일","월요일","화요일","수요일","목요일","금요일","토요일"]

    for item in range(1, year):
        if is_leap(item):
            total_days = total_days + 366
        else:
            total_days = total_days + 365

    for item in range(1, month):
        total_days = total_days + year_month_days[item]

    if month >= 3:
        if is_leap(year):
            total_days = total_days + 1
        else:
            total_days = total_days + 0

    total_days += day
    remainder = total_days % 7
    return day_names[remainder]

if __name__ == "__main__":
    year, month, day = input_date()
    day_name = get_day_name(year, month, day)    
    print(day_name)
