import re
from collections import Counter
from statistics import mean, stdev

fp = open('localhost_access_log.txt')
data = []

try:
# 1. 전체 로그보기(ip: .. 날짜: .. 뷰페이지: )
    for rd in fp:
        ip = re.search('[\d.:]+', rd)
        # print(ip.group())
        date = re.search('\[([\w/:]+)', rd)
        # print(date.group(1))
        view = re.search('"GET ([\w/.-]+) ([\w./]+)"', rd)
        # print(view.group())
        b_size = re.search(' ([\d-]+)$', rd)
        print(b_size.group(1))
        b_size = 0 if b_size == '-' else int(b_size)

        data.append((ip,date,view,b_size))

    for n in data:
        print("ip:",n[0])
        print("dt:",n[1])
        print("view:",n[2])
        print("bsize:",n[3])
        print("-----------")

# 4. 전체전송바이트 사이즈 와 평균, 표준편차
    b_size_sum = sum([n[3] for n in data])
    b_size_mean = mean([n[3] for n in data])
    b_size_std = stdev([n[3] for n in data])

    print("전체사이즈:", b_size_sum)
    print("사이즈평균:", b_size_sum)
    print("사이즈표준편차:", b_size_sum)

except Exception as err:
    print('not found')