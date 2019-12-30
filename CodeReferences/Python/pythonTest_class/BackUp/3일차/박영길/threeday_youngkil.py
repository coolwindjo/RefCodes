import csv
import copy
import statistics
import operator
import sys
import openpyxl
from openpyxl.chart import BarChart, LineChart, Reference

import sqlite3


fp = open('CCTV_in_Seoul.csv', encoding='utf-8')
rd = csv.reader(fp)
print(rd)

data = []
for idx, item in enumerate(rd) :
    if idx == 0 :
        data.append(item)
    else :
        imsi_list = []
        for idx2, n in enumerate(item) :
            if idx2 == 0 :
                imsi_list.append(n)
            else :
                imsi_list.append(int(n))
        data.append(imsi_list)




    # print(idx, item)
    # data.append(item)

print(data)
data_1 = [  n[1] for n in data ]
data_11 = copy.deepcopy(data_1[1:])   #data_11 == '소계 column
print(data_11, len(data_11))
print('-'*30)
print('1. cctv 소계의 평균을 구하시요')
print('-'*30)
mean_data_11 = statistics.mean(data_11)
print(mean_data_11)
print('\n\n\n')
print('-'*30)
print('2. cctv 소계가 가장많은 기관명, 소계를 구하시요')


# for item in data :
#     print (item)

max_data_11 = max(data_11)


max_data_11_list = []
for idx, item in enumerate(data_11) :
    if max_data_11 == item :
        # print(idx, item)
        max_data_11_list.append(idx)

for idx in max_data_11_list :
    print('기관명 : ',data[idx+ 1][0], '    소계',  data[idx+1][1])

print('-'*30)
print('3. cctv 소계가 가장많은 top5 기관명 소계를 구하시요')
print('-'*30)

data11_sort = copy.deepcopy(data_11)
data11_dict = dict()
for idx, item in enumerate(data11_sort) :
    data11_dict[idx] = item

# print(data11_dict)

# print('-----------------------------')
sorted_d = sorted(data11_dict.items(), key=operator.itemgetter(1), reverse=True)
# print(sorted_d)
max_data_11_key = []
for idx, item in enumerate( sorted_d ) :

    max_data_11_key.append(item)
    if idx == 4 :
        break


for idx, value in max_data_11_key :

    print(data[idx+ 1][0], '    소계',  data[idx+1][1])

print('4. 기관별 cctv소계에 대한 라인차트를 엑셀에 그리시요')

print(len(data_11))

# sys.exit()

# wb = openpyxl.load_workbook('chart.xlsx')
wb = openpyxl.Workbook()
ws = wb.active
ws = wb['Sheet']




for idx, value in enumerate(data_11) :

    ws.append([data[idx+ 1][0],  data[idx+1][1]])



# chart = BarChart()
chart = LineChart()
chart.width = 20 # 기본값 15
chart.height = 15  # 기본값 7
chart.title = 'CCTV 소계'
chart.x_axis.title = '소계'
chart.y_axis.title = '기관'
chart.style        = 11
# cdata = Reference(ws, range_string='Sheet!B1:C4')
cdata = Reference(ws, min_col= 2, max_col= len(data_1),
                      min_row =1, max_row =1 )
# cat   = Reference(ws, range_string='Sheet!A2:A4')
chart.add_data(cdata, titles_from_data=True)
# chart.set_categories( cat )
ws.add_chart(chart, 'F1')
wb.save('chart.xlsx')


print('6. cctv db 의 cctv 테이블에 기관명 소계를 저장하시요')


def createTable() :
    try :

        sql = "create table if not exists "  \
                  "student(기관 varchar(20), 소계 int )"
        db = sqlite3.connect('cctb.db')
        db.execute(sql)
        db.close()
        print('create success')
    except Exception as err :
        print('에러', err)

try :
    sql = "insert into student(기관, 소계)"  \
               "values(?,?)"
    db = sqlite3.connect('cctb.db')

    data_db = []
    for idx, value in enumerate(data_11) :
        # print(idx, value)
        # data[idx+ 1][0],  data[idx+1][1]])
        # print((data[idx+ 1][0],  data[idx+1][1]))
        data_db.append((data[idx+ 1][0],  data[idx+1][1]) )

    # for item in data_db :
    #     print(item)

    # sys.exit()
    db.executemany(sql, data_db)
    db.commit()

    db.close()
    print('insert success')
except Exception as err :
    print('에러', err)


createTable()
# insertTable1()
