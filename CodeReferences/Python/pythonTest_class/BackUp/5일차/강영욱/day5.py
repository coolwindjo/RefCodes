# 로그분석(정규식을 이용할것) 1번과 4번만 해도 기본점수이상
# 1. 전체 로그보기(ip: .. 날짜: .. 뷰페이지: )
# 2. ip별 방문 횟수( 000.000.000.000:x회)
# 3. 페이지별 뷰수(ex a.htm:x회 )
# 4. 전체전송바이트 사이즈와 평균, 표준편차
# 5. 가장많이 방문한 ip 와 방문수
# 6. 가장많이 방문한 ip 와 방문수 top 5
# 7. 엑셀 그래프로 저장(페이지별뷰수, ip별방문수 2개의 그래프)

import re
import statistics
from collections import Counter

fp = open('localhost_access_log.txt','r')

def ViewLog():
    fp.seek(0)
    for rd in fp:
        ip = re.search('\d{1}:\d{1}:\d{1}:\d{1}:\d{1}:\d{1}:\d{1}:\d{1}|\d{1,3}.\d{1,3}.\d{1,3}.\d{1,3}',rd)
        print( 'ip:',ip.group() )
        date = re.search('\[([\w./:]+)',rd)
        print( '날짜:',date.group(1) )
        page = re.search('(GET|POST) (\S+)',rd)
        print( '뷰페이지:',page.group(2) )

def CountPerIp():
    fp.seek(0)
    data = []
    for rd in fp:
        ip = re.search('\d{1}:\d{1}:\d{1}:\d{1}:\d{1}:\d{1}:\d{1}:\d{1}|\d{1,3}.\d{1,3}.\d{1,3}.\d{1,3}',rd)
        data.append(ip.group())

    c = Counter( data )
    for k,v in c.items():
        print('%s: %d회'%(k,v))

def CountViewPerPage():
    fp.seek(0)
    data = []
    for rd in fp:
        page = re.search('(GET|POST) (\S+)',rd)
        data.append(page.group())

    c = Counter( data )
    for k,v in c.items():
        print('ip: %s, 방문수: %d회'%(k,v))

def TotalByteSize():
    fp.seek(0)
    data = []

    for rd in fp:
        size = re.search('-$|\d+$',rd)
        if size.group() == '-':
            data.append(int(0))
        else:
            data.append(int(size.group()))

    # print(data)
    print('전체전송바이트 사이즈:',sum(data))
    print('전체전송바이트 평균:',statistics.mean(data))
    print('전체전송바이트 표준편차:',statistics.stdev(data))

def MaxIp():
    fp.seek(0)
    data = []
    for rd in fp:
        ip = re.search('\d{1}:\d{1}:\d{1}:\d{1}:\d{1}:\d{1}:\d{1}:\d{1}|\d{1,3}.\d{1,3}.\d{1,3}.\d{1,3}',rd)
        data.append(ip.group())

    c = Counter( data )
    d = c.most_common(1)
    for k,v in d:
        print('ip:%s, 방문수: %d회'%(k,v))

def MaxIp5():
    fp.seek(0)
    data = []
    for rd in fp:
        ip = re.search('\d{1}:\d{1}:\d{1}:\d{1}:\d{1}:\d{1}:\d{1}:\d{1}|\d{1,3}.\d{1,3}.\d{1,3}.\d{1,3}',rd)
        data.append(ip.group())

    c = Counter( data )
    d = c.most_common(5)
    for k,v in d:
        print('ip:%s, 방문수: %d회'%(k,v))

def DrawChart():
    fp.seek(0)
    print('DrawChart')

def FinishView():
    fp.seek(0)
    print('FinishView')
    exit()

# =========================================
menu = {1:ViewLog,
        2:CountPerIp,
        3:CountViewPerPage,
        4:TotalByteSize,
        5:MaxIp,
        6:MaxIp5,
        7:DrawChart,
        8:FinishView}

while True:
    print('=========================================')
    print("1. 전체 로그보기")
    print("2. ip별 방문 횟수")
    print("3. 페이지별 뷰수")
    print("4. 전체전송바이트 사이즈와 평균, 표준편차")
    print("5. 가장많이 방문한 ip 와 방문수")
    print("6. 가장많이 방문한 ip 와 방문수 top 5")
    print("7. 엑셀 그래프로 저장")
    print("8. 프로그램 종료")
    num = int(input("메뉴를 선택하시요:"))

    print(num)
    if num < 1 or num > 8:
        print('잘못 입력하셨습니다. 다시 입력해주세요')
    else:
        menu[num]()

fp.close()


# 메뉴를 선택하시요:
# 1.번
# ip:
# 날짜:
# 뷰페이지: /aa.png
# ----------
# ..
# 2.번
# 0:0:0:0:0:0:0:1:n번
# 192.168.123.240:n번
# ..
# 3 번:
# aa.png: 번
# tomcat.png;X번
# 4.번
# 전체전송사이즈:
#
# 5 번:
# 가장많이 방문ip: xxx.xxx.xxx.xxx
#
# 6번:
# 차트로 그리기(map plot lib)(페이지별뷰수, ip별방문수)


