import re
from statistics import *
from collections import Counter
import openpyxl
from openpyxl.chart import BarChart, LineChart, Reference

def openFile():
    fp = open('localhost_access_log.txt','r')
    rd = fp.readlines()
    fp.close()
    rd = [n.strip() for n in rd]    #strip()함수를 써서 공백, 개행을 삭제할 수 있음
    return rd

def makeExcel():
    rd = openFile()
    #페이지별 뷰수
    pageList = []
    for n in rd:
        pages = re.search('(GET|POST) (\S+)',n)
        pageList.append(pages.group(2))
    counterPage = Counter( pageList )
    cList = counterPage.most_common()
    print( cList )

    #ip별 방문수
    ipList = []
    rd = openFile()
    for n in rd:
        ips = re.search('\d{1,3}.\d{1,3}.\d{1,3}.\d{1,3}',n)
        ipList.append(ips.group())
    counterIp = Counter( ipList )
    ipList = counterIp.most_common()
    print( ipList )

    wb = openpyxl.Workbook()
    ws = wb.active
    ws.append(["페이지", "뷰수", "IP", "방문"])

    # for
    # ws.append([name, kor, eng])


def topFiveVisitIp():
    ipList = []
    rd = openFile()
    for n in rd:
        ips = re.search('\d{1,3}.\d{1,3}.\d{1,3}.\d{1,3}',n)
        ipList.append(ips.group())
    c = Counter( ipList )
    for n in c.most_common(5):
        print('ip:',n[0])

def mostVisitIp():
    ipList = []
    rd = openFile()
    for n in rd:
        ips = re.search('\d{1,3}.\d{1,3}.\d{1,3}.\d{1,3}',n)
        ipList.append(ips.group())
    c = Counter( ipList )
    print("가장많이 방문ip:{}".format(*c.most_common(1)[0]))

def totBytes():
    data = []
    rd = openFile()
    for n in rd:
        bytes = re.search('\d+$',n)
        exceptionCase = re.search('\-$',n)
        if exceptionCase != None:
            data.append(int(0))
        else:
            data.append(int(bytes.group()))

    print("전체전송사이즈:", sum(data))
    print("전체전송사이즈 평균", mean(data))
    print("전체전송사이즈 표준편차", stdev(data))

def numPage():
    pageList = []
    rd = openFile()
    for n in rd:
        pages = re.search('(GET|POST) (\S+)',n)
        pageList.append(pages.group(2))
    c = Counter( pageList )
    for page, view in c.most_common():
        print("ip:",page,":",view,"번")

def numVisit():
    ipList = []
    rd = openFile()
    for n in rd:
        ips = re.search('\d{1,3}.\d{1,3}.\d{1,3}.\d{1,3}',n)
        ipList.append(ips.group())
    c = Counter( ipList )
    for ip, visit in c.most_common():
        print("ip:",ip,":",visit,"번")

def totLog():
    rd = openFile()
    for n in rd:
        ips = re.search('\d{1,3}.\d{1,3}.\d{1,3}.\d{1,3}',n)
        days = re.search('\[([\w/]+)',n)
        views = re.search('(GET|POST) (\S+)',n)

        print("ip:",ips.group())
        print("날짜:",days.group(1))
        print("뷰페이지:",views.group(2))

menu = {1:totLog, 2:numVisit,3:numPage,4:totBytes,5:mostVisitIp,6:topFiveVisitIp,7:makeExcel}

while True:
    print('====================================================='
          '1. 전체 로그보기(ip: .. 날짜: .. 뷰페이지: )\n'\
          '2. ip별 방문 횟수( 000.000.000.000:x회)\n' \
          '3. 페이지별 뷰수(ex a.htm:x회 )\n'\
          '4. 전체전송바이트 사이즈 와 평균, 표준편차\n'\
          '5. 가장많이 방문한 ip 와 방문수\n'\
          '6. 가장많이 방문한 ip 와 방문수 top 5\n'\
          '7. 엑셀 그래프로 저장(페이지별뷰수, ip별방문수 2개의 그래프)\n'
          '=====================================================', sep='\n')

    nSel = int( input('메뉴를 선택하세요:') )
    menu[nSel]()
