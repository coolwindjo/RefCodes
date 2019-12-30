import openpyxl
from openpyxl.chart import BarChart,LineChart,Reference
def xlWrite():
    wb = openpyxl.Workbook()
    ws = wb.active
    ws.append(['이름','국어','영어'] )
    ws.append(['홍길동',40,80] )
    ws.append(['이순신',50,90] )
    ws.append(['임꺽정',70,60] )
    wb.save('xlsTest/result/chart.xlsx')
wb  = openpyxl.load_workbook('xlsTest/result/chart.xlsx')
ws = wb['Sheet']
# chart = BarChart()
chart = LineChart()
chart.width = 20 #기본값 15
chart.height = 15 # 기본값 7
chart.title= '성적데이터'
chart.x_axis.title = '이름'
chart.y_axis.title = '점수'
chart.style = 11
# cdata = Reference( ws, range_string='Sheet!B1:C4' )
cdata = Reference( ws,min_col=2, max_col=3,
                   min_row=1, max_row=4)
cat = Reference( ws, range_string='Sheet!A2:A4')
chart.add_data(cdata,titles_from_data=True)
chart.set_categories( cat )
ws.add_chart( chart, 'F1')
wb.save('xlsTest/result/chart.xlsx')














