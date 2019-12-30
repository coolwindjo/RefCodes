import csv
import statistics
import openpyxl
from openpyxl.chart import BarChart, LineChart, Reference

# 1. cctv 소계의 평균을 구하시요
fp = open('CCTV_in_Seoul.csv', encoding='utf-8')
rd = csv.reader(fp)

data=[]

def makeData():
    next(rd)
    for d1,d2,d3,d4,d5,d6 in rd:
        data.append((d1, int(d2),int(d3), int(d4), int(d5), int(d6)))
    fp.close()

makeData()
print(data)
mean = statistics.mean(n[1] for n in data)
print("1. cctv 소계의 평균 : ", mean)

# 2. cctv 소계가 가장많은 기관명, 소계를 구하시요
mx = max(data, key=lambda v:v[1])
print("2. cctv 소계가 가장많은 기관명, 소계 : ", mx[0], mx[1])


# 3. cctv 소계가 가장많은 top5 기관명 소계를 구하시요


# 4. 기관별 cctv소계에 대한 라인차트를 엑셀에 그리시요
# wb = openpyxl.Workbook()
# ws = wb.active
# ws.title = 'sheet1'
# ws.append(["기관명","소계","2013년도 이전","2014년","2015년","2016년"])


# 5. 2013년도 대비 cctv증가율에 대해 다음 과 같이
# 출력하시요.
# (cctv증가율:  2013년도 이전/(2014년+2015년+2016년)
#
# 기관명 cctv증가율
# ================
# 강남구  0.5
# 강동구  0.3
# ....
# 6. cctv db 의 cctv 테이블에 기관명 소계를 저장하시요
