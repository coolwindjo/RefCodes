import csv
import openpyexcel
from openpyexcel.chart import BarChart, LineChart, Reference

data = []
sorteddata = []
count = 0

def readData():
    cnt = 0
    fp = open('CCTV_in_Seoul.csv', encoding='UTF-8')
    rd = csv.reader(fp)
    for name, sogye, y2013, y2014, y2015, y2016 in rd:
        if cnt > 0:
            data.append((name, int(sogye), int(y2013), int(y2014), int(y2015), int(y2016)))
        cnt += 1
    fp.close()
    return cnt

count = readData() - 1
sogyeMax = 0

print( "1. CCTV 소계 평균: ", sum( [n[1] for n in data] )/count )
sogyeMax = max( data, key=lambda v:v[1] )
print( "2. CCTV 소계가 가장 많은 기관 명: ", sogyeMax[0], "소계: ", sogyeMax[1])

sorteddata = list(reversed(sorted(data, key=lambda v:v[1])))
print("3. CCTV 소계가 가장 많은 top5 기관명의 소계: ", sorteddata[0:5])

print("4. 기관별 CCTV 소계에 대한 라인차트를 엑셀에 그리시오")

wb = openpyexcel.Workbook()
ws = wb.active
ws.append(['기관명','소계','2013년도 이전', '2014년', '2015년', '2016년'] )

for name, sogye, y2013, y2014, y2015, y2016 in data:
    ws.append([name, int(sogye), int(y2013), int(y2014), int(y2015), int(y2016)])

wb.save('CCTV.xlsx')
chart = BarChart()
chart.width = 20
chart.height = 15
chart.title = 'CCTV 소계'
chart.x_axis.title = '년도'
chart.y_axis.title = '기관'
chart.style = 11
cdata = Reference( ws,min_col=2, max_col=5,
                   min_row=1, max_row=ws.max_row )
cat = Reference( ws,min_col=1,
                   min_row=2, max_row=ws.max_row )

chart.add_data(cdata, titles_from_data=True)
chart.set_categories( cat )
ws.add_chart(chart, 'F1')
wb.save('CCTV.xlsx')



#
# fp.close()
# print("남아수 총 합: ", mTot)
# print("남아 수가 가장 많은 년도: ", mMaxYear, "남아 수: ", mMax)
# # 2000년 이후 남아수 여아수에 대해 바차트를 그린다.
# chart = BarChart()
# chart.width = 20
# chart.height = 15
# chart.title = '미국 연도 별 아이 수'
# chart.x_axis.title = '성별'
# chart.y_axis.title = '아이 수'
# chart.style = 11
# cdata = Reference( ws,min_col=2, max_col=3,
#                    min_row=1, max_row=ws.max_row )
# cat = Reference( ws,min_col=1,
#                    min_row=2, max_row=ws.max_row )
#
# chart.add_data(cdata, titles_from_data=True)
# chart.set_categories( cat )
# ws.add_chart(chart, 'F1')
# wb.save('births.xlsx')
#
# f2000 = filter(lambda v:int(v[0]) >=2000, data)
#
# for a, b, c in f2000:
#     print(a, b, c)
# # cctvAvg = st.mean(data[1])
# # print(cctvAvg)
#



