def input_date():
    year = int(input("Enter the year: "))
    month = int(input("Enter the month:"))
    day = int(input("Enter the day:"))
    return year, month, day

def is_leap(year):
    if year % 400 == 0:
        return True
    elif year % 100 == 0:
        return False
    elif year % 4 == 0:
        return True
    else:
        return False

def get_day_name(year, month, day):

    total_days = 0

    year_month_days = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    day_names = ["Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"]

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