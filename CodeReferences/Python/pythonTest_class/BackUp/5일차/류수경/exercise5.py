# 로그분석(정규식을 이용할것) 1번과 4번만 해도 기본점수이상
# 1. 전체 로그보기(ip: .. 날짜: .. 뷰페이지: )
# 2. ip별 방문 횟수( 000.000.000.000:x회)
# 3. 페이지별 뷰수(ex a.htm:x회 )
# 4. 전체전송바이트 사이즈 와 평균, 표준편차
# 5. 가장많이 방문한 ip 와 방문수
# 6. 가장많이 방문한 ip 와 방문수 top 5
# 7. 엑셀 그래프로 저장(페이지별뷰수, ip별방문수 2개의 그래프)

import re
from statistics import stdev
from collections import Counter

raw_data= []
logs=[]

def readFile():
    fp= open('localhost_access_log.txt','r')
    global raw_data
    raw_data = fp.readlines()
    fp.close()
    createLogs()

def createLogs():
    global logs
    for data in raw_data:
        ip = re.search('(\d{3}.\d{3}.\d{3}.\d{2,3})',data)
        if ip == None:
            ip = re.search('\d:\d:\d:\d:\d:\d:\d:\d',data)
        date = re.search('\[([\w/:]+)',data)
        bytesize = re.search('\d+$',data)
        bytesize = 0 if bytesize == None else int(bytesize.group())
        logs.append((ip.group(),date.group(1),bytesize))

def viewTotalLogs():
    global logs
    for log in logs:
        print(f'ip: {log[0]}, 날짜: {log[1]}, 뷰페이지: {log[2]}')

def calByteSize():
    bytes=[]
    for log in logs:
        bytes.append(log[2])

    sumValue = sum(bytes)
    #sumValue = sum(n[2] for n in logs)
    avgValue  = sum(bytes)/len(bytes)
    stdevValue  = stdev(bytes)
    print('전체전송사이즈: %d, 평균: %f, 표준편자: %f' %(sumValue,avgValue,stdevValue))

def topIpView():
    c = Counter(logs)
    mx = c.most_common(1)
    print(f'가장많이 방문한 ip: {mx[0][0][0]} 와 방문수 : {mx[0][1]}')

def top5IpView():
    c = Counter(logs)
    mx = c.most_common(5)
    for n in mx:
        print(f'가장많이 방문한 Top5 ip: {n[0][0]} 와 방문수 : {n[1]}')

def countIp():
    c = Counter(logs)
    m = c.most_common()
    for n in m:
        print(f'IP별 방문 횟수: IP: {n[0][0]} 방문횟수: {n[1]}')

def countView():
    pass

readFile()

# 1. 전체 로그보기(ip: .. 날짜: .. 뷰페이지: )
viewTotalLogs()

# 2. ip별 방문 횟수( 000.000.000.000:x회)
countIp()

#3. 페이지별 뷰수(ex a.htm:x회 )
countView()

# 4. 전체전송바이트 사이즈 와 평균, 표준편차
calByteSize()

# 5. 가장많이 방문한 ip 와 방문수
topIpView()

# 6. 가장많이 방문한 ip 와 방문수 top5
top5IpView()
