# 년월일을 입력 받는다.
year = int(input("년도를 입력하시오: "))
month = int(input("월을 입력하시오: "))
day = int(input("일을 입력하시오: "))

total_days = 0
# 달별 날수를 리스트로 저장
year_month_days = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

# 서기 1년부터 year-1 까지의 각 년도 별 날수를 합한다. 
for item in range(1, year):
    if item % 400 == 0:                # 400으로 나뉘는 해 (윤년)
        total_days = total_days + 366
    elif item % 100 == 0:              # 100으로 나뉘는 해 (윤년 아님)
        total_days = total_days + 365
    elif item % 4 == 0:                # 4로 나뉘는 해 (윤년)
        total_days = total_days + 366
    else:
        total_days = total_days + 365

# 1월 달부터 month-1 까지의 각 달의 날수를 합한다.
for item in range(1, month):
    total_days = total_days + year_month_days[item]

# 입력된 달이 3이상이고 해당년도가 윤년일 경우 1을 추가
if month >= 3:
    if year % 400 == 0:
        total_days = total_days + 1
    elif year % 100 == 0:
        total_days = total_days + 0
    elif year % 4 == 0:
        total_days = total_days + 1
    else:
        total_days = total_days + 0
        
total_days += day
# 총 날수를 7로 나눈 나머지를 구한다.
remainder = total_days % 7

if remainder == 0:
    print("일요일 입니다.")
elif remainder == 1:
    print("월요일 입니다.")
elif remainder == 2:
    print("화요일 입니다.")
elif remainder == 3:
    print("수요일 입니다.")
elif remainder == 4:
    print("목요일 입니다.")
elif remainder == 5:
    print("금요일 입니다.")
elif remainder == 6:
    print("토요일 입니다.")
