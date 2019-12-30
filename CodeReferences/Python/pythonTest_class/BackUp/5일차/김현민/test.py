import re
from collections import Counter
from statistics import stdev
import numpy

log = []
log1 = []
log2 = []
mean1 = []
totalbyte = 0;
def readfile():
    fp = open('localhost_access_log.txt')
    rd = fp.readlines()
    fp.close()
    return rd

a = readfile()

for n in a:
    # print(n)
    try:
        match = re.search('(\d{3}.\d{3}.\d{3}.\d{2}) |(\d.\d.\d.\d.\d.\d.\d.\d) ',n)
        log1.append(match.group())
        match1 = re.search('\[([\w/: +]+)',n)
        match2 = re.search('(GET|POST) (\S+)',n)
        log2.append(match2.group(2))
        log.append((match.group(), match1.group(1), match2.group(2)))
        match3 = re.findall('\d\w+',n)
        b = int(match3.pop())
        mean1.append(b)
        totalbyte += b
    except Exception as err:
        print('not found')

print("Total byte: ", totalbyte)
print("평균: ", sum(mean1) / len(mean1))
print("표준편차: ", numpy.std(mean1))

def test1():
    for n1,n2,n3 in log:
        print("ip: ", n1,"날짜: " ,n2,"뷰페이지: ",n3 )

def test2():
    kk = []
    c = Counter( log1 )
    dd = 0
    for n in c:
        print(n, ':', c[n])
        kk.append((n, int(c[n])))
        if dd < int(c[n]):
            dd = int(c[n])
            e = n
    print('가장 많이 방문한 IP:', e, '횟수:', dd)
    k = 0
    sList = sorted(kk,key=lambda  v:v[1], reverse=True)[:5]
    for n1, n2 in sList:
        print('Top5 방문한 IP:', n1, '횟수:', n2)

def test3():
    c = Counter( log2 )
    for n in c:
        print(n, ':', c[n])

while True:
    cnt = input("메뉴를 선택하시오:\n"
          "1. ip: 날짜: 뷰페이지:\n"
          "2. 0:0:0:0:0 : n번\n"
          "3번 aa.png: n번\n"
                "종료 4번")
    if cnt == '1':
        test1()
    if cnt == '2':
        test2()
    if cnt == '3':
        test3()
    if cnt == '4':
        break
