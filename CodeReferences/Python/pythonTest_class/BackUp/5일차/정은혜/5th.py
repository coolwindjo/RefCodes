# 로그분석(정규식을 이용할것) 1번과 4번만 해도 기본점수이상
# 1. 전체 로그보기(ip: .. 날짜: .. 뷰페이지: )
# 2. ip별 방문 횟수( 000.000.000.000:x회)
# 3. 페이지별 뷰수(ex a.htm:x회 )
# 4. 전체전송바이트 사이즈 와 평균, 표준편차
# 5. 가장많이 방문한 ip 와 방문수
# 6. 가장많이 방문한 ip 와 방문수 top 5
# 7. 엑셀 그래프로 저장(페이지별뷰수, ip별방문수 2개의 그래프)
import re
import sys
from collections import Counter
from statistics import *

file = open('localhost_access_log.txt')
data =[]
total_Data =[]

def ReadFile():
    while True:
        line = file.readline()
        try:escape=line.index('\n')
        except:escape=len(line)

        if line:
            data.append(line[0:escape])
        else:
            break

    file.close()
    # print(len(data))#1127개 라인

# 1. 전체 로그보기(ip: .. 날짜: .. 뷰페이지: )
def log():
    try:
        for line in file:
            # print(line)   #1127개 라인
            # ips = re.search('\d{1,3}.\d{3}.\d{3}.\d{3}|0:0:0:0:0:0:0:1', line )
            ips = re.search('[\d.:]+ ',line )
            dates = re.search('\[([\w/:]+)',line )
            files = re.search('(GET) (\S+)',line )
            size = re.search('\d+$|-',line )
            print( 'ip:', ips.group() ,'date:',dates.group(),'file:',files.group(2),'size:',size.group() )

            total_Data.append((ips.group(),dates.group(),files.group(2),size.group()) )
    except Exception as err:
        print('not found')


# 4. 전체전송바이트 사이즈 와 평균, 표준편차
def fn4():
    total_size=[]
    for line in data:
        size = re.findall('\d+$', line )
        total_size.append(size)
    print(sum(n for n in total_size))

# 5. 가장많이 방문한 ip 와 방문수
# 6. 가장많이 방문한 ip 와 방문수 top 5
def fn56():
    IPdata =[]
    for line in data:
        ips = re.findall('\d{1,3}.\d{3}.\d{3}.\d{3}|0:0:0:0:0:0:0:1', line )
        IPdata.append(ips)
    print(IPdata)
    Top = Counter( IPdata )
    #print( c['aa'] )
    print('가장많이 방문한 IP:',Top.most_common(1),'방문수:')
    print('가장많이 방문한 IP top5:',Top.most_common(5), '방문수:')


# ReadFile()
log()   #1번문제
fn4()   #4번문제
fn56()   #5,6번문제




