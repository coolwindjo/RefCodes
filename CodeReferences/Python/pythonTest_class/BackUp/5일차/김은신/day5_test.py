# localhost_access_log.txt
import re
from collections import Counter
import openpyxl
import numpy
# from statistics import mean, stdev
import statistics
from openpyxl.chart import BarChart, LineChart, Reference

fp = open("localhost_access_log.txt")
data = fp.readlines()
print(data)
fp.close()

############################## 1
def showAllLog():
    for n in data:
        match = re.findall("(^[\d.:]+)[ \w[-]+([\w/:]+) \+[0-9]{4}\] \"(GET|POST) ([\w/.]+)", n)
        # print(match)
        print("IP address:", match[0][0])
        print("Date:", match[0][1])
        print("View page:", match[0][3])

############################## 2
def countIP():
    print("IP별 방문 횟수")
    ipList = []
    for n in data:
        match = re.findall("(^[\d.:]+)[ \w[-]+([\w/:]+) \+[0-9]{4}\] \"(GET|POST) ([\w/.]+)", n)
        ipList.append(match[0][0])
    ipCount = Counter(ipList)
    for n in ipCount.items():
        print("IP:{0}:{1}회".format(*n))
    print("\n")

############################## 3
def countPage():
    print("Page별 View 수")
    pageList = []
    for n in data:
        match = re.findall("(^[\d.:]+)[ \w[-]+([\w/:]+) \+[0-9]{4}\] \"(GET|POST) ([\w/.]+)", n)
        pageList.append(match[0][3])
    pageCount = Counter(pageList)
    for n in pageCount.items():
        print("{0} : {1}회".format(*n))
    print("\n")

############################## 4
def allByteSize():
    size = 0
    sizeList = []
    for n in data:
        item = re.search('\d+$', n)
        # print(match.group())
        if item != None:
            size += int(item.group())
            sizeList.append(size)
    # print("all:", sum(n[3] for n in data), "mean:", mean(n[3] for n in data), "stdev:", stdev(n[3] for n in data))
    print("All sent byte size:", size, ", Mean:", statistics.mean(sizeList), ", stdev:", statistics.stdev(sizeList))
    # print("All sent byte size:", sum(match.group()), ", Mean:", statistics.mean(*match.group()), ", stdev:", statistics.stdev(*match.group()))

    # byteSum = 0
    # cnt = 0
    # for n in data:
    #     match = re.search('\d+$', n)
    #     if match != None:
    #         byteSum += int(match.group())
    #         cnt += 1
    # print("All sent byte size: ", byteSum, ", Mean:", byteSum/cnt, "표준편차:", numpy.std(byteSum))
    print("\n")

############################## 5
def printMaxIP():
    ipList = []
    for n in data:
        match = re.findall("(^[\d.:]+)[ \w[-]+([\w/:]+) \+[0-9]{4}\] \"(GET|POST) ([\w/.]+)", n)
        ipList.append(match[0][0])
    ipCount = Counter(ipList)
    print("Top1 IP:", ipCount.most_common(1)[0][0], ", 방문수:", ipCount.most_common(1)[0][1])
    print("\n")

############################## 6
def printTop5():
    print("========= Top5 IP =========")
    ipList = []
    for n in data:
        match = re.findall("(^[\d.:]+)[ \w[-]+([\w/:]+) \+[0-9]{4}\] \"(GET|POST) ([\w/.]+)", n)
        ipList.append(match[0][0])
    ipCount = Counter(ipList)
    topdata = ipCount.most_common(5)
    cnt = 1
    for n in topdata:
        # print(n)
        print(cnt, ": {0}, {1}회".format(n[0], n[1]))
        cnt += 1
    print("\n")


############################## 7
def saveExcel():
    print("<Save Excel>")

menu = {1:showAllLog, 2:countIP, 3:countPage, 4:allByteSize, 5:printMaxIP, 6:printTop5, 7:saveExcel, 0:exit}
while True:
    print("\n==========================================================")
    print('1. 전체 로그보기', '2. ip별 방문 횟수', '3. 페이지별 뷰수', '4. 전체 전송 바이트 사이즈와 평균, 표준편차',
    '5. 가장많이 방문한 ip와 방문수', '6. 가장많이 방문한 ip와 방문수 Top5', '7. 엑셀 그래프로 저장', '0: Exit',sep='\n')
    nSel = int( input('메뉴를 선택하세요...: '))
    menu[nSel]()
