import csv
import sqlite3
import re
from collections import Counter
from statistics import mean,stdev
import statistics

size_data = []

#1. 전체 로그보기(ip: .. 날짜: .. 뷰페이지: )
def viewFullLog():
    print('-'*20)
    print('1.번')
    print('-'*20)

    fp = open('localhost_access_log.txt',encoding='utf-8')
    rd = csv.reader(fp)
    iCnt = 1
    for n in rd:
        print(iCnt,'번째')
        iCnt += 1
        n = str(n)
        ip = re.search('(\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}|\d:\d:\d:\d:\d:\d:\d:\d)', n )
        print('ip:', ip.group())
        date_t = re.search('\[([\w/:]+)', n )
        print('날짜:',date_t.group())
        view = re.search('(GET|POST) (\S+)', n )
        print( '뷰페이지:',view.group(2) )
        print('-'*20)
    fp.close()

def collectTransferBytes():
    print('-'*20)
    print('4.번')
    print('-'*20)
    fp = open('localhost_access_log.txt',encoding='utf-8')
    rd = csv.reader(fp)
    for n in rd:
        n = str(n)
        view = re.search('(GET|POST) (\S*) HTTP/1.1["] (200|404|401) (\d+)' , n )
        if view:
            s3 = view.group(4)
            # print(s3)
            size_data.append(int(s3))
        else:
            view = re.search('(GET|POST) (\S*) HTTP/1.1["] (\d+) \-', n )
            if view:
                size_data.append(0)
            else:
                print(n)

    print('전체전송바이트 total:',sum(size_data))
    print('전체전송바이트 average:',mean(size_data))
    print('전체전송바이트 표준편차:',statistics.stdev(size_data))
    print('-'*20)


def IpTimes():
    fp = open('localhost_access_log.txt',encoding='utf-8')
    rd = fp.read()
    my = re.findall('(\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}|\d:\d:\d:\d:\d:\d:\d:\d)', rd, re.MULTILINE)

    c = Counter(my)
    print('-'*20)
    print('2.번 ip별 방문 수')
    print('-'*20)
    # print(c.most_common())
    for ip, time in c.most_common():
        print(ip,'-',time)

    print('-'*20)
    print('5.번 ip별 top 방문 수')
    print('-'*20)
    print(c.most_common(1)[0][0],'-',c.most_common(1)[0][1])

    print('-'*20)
    print('6.번 ip별 top 5 방문 수')
    print('-'*20)
    # print(c.most_common(5))
    for ip, time in c.most_common(5):
        print(ip,'-',time)
    fp.close()

def ViewTimes():
    fp = open('localhost_access_log.txt',encoding='utf-8')
    rd = fp.read()
    my = re.findall('(GET|POST) (\S+)', rd, re.MULTILINE)

    c = Counter(my)
    print('-'*20)
    print('3.번 페이지별 방문 수')
    print('-'*20)

    for n in c.most_common():
        print(n[0][1],'-',n[1])
    # for command, page, count in c.most_common():
    #     print(page,'-',count)

    fp.close()

viewFullLog()
ViewTimes()
IpTimes()
collectTransferBytes()


