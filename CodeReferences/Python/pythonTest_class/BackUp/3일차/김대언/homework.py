import csv
import openpyxl
from openpyxl.chart import LineChart,Reference

fp = open('CCTV_in_Seoul.csv', encoding='utf-8')
rd = csv.reader(fp)

cctvList = []

def q1():
    index = -1
    sum = 0
    for n in rd:
        if index > -1:
            cctvList.append(n)
            sum += int(n[1])
            index += 1
        else:
            index += 1

    print('문제1: ', sum/index)

def q2():
    mx = max(cctvList, key=lambda v:v[1])
    print('문제2:', mx[0], mx[1])


def q3():
    print('문제3:')
    tempList = cctvList.copy()
    cnt = 0
    while True:
        cnt += 1
        mx = max(tempList, key=lambda v:v[1])
        print(str(cnt)+'위:', mx[0], mx[1])
        tempList.remove(mx)
        if cnt == 5:
            break

def q4():
    wb = openpyxl.Workbook()
    ws = wb.active
    ws.append(('기관명', '소계', '2013년도 이전', '2014년', '2015년', '2016년'))
    for n in cctvList:
        ws.append(n)

    chart = LineChart()
    cdata = Reference(ws, range_string='Sheet!B1:B26')
    cat = Reference(ws, range_string='Sheet!B1')
    chart.add_data(cdata, titles_from_data=True)
    chart.set_categories(cat)
    ws.add_chart(chart, 'H1')
    wb.save('CCTV_in_Seoul.xlsx')


q1()
q2()
q3()
q4()

fp.close()
