import re
import math
import statistics

def fileRead():
    fp = open('localhost_access_log.txt','r')
    rd = fp.readlines()
    rd = [n.strip() for n in rd]
    return rd

def test1():
    data = fileRead()
    for n in data:
        try:
            # match = re.search('\w{3}.\w{3}.\w{3}.\w{3} | 0+', n)
            match1 = re.search('0:[\d:]+|\w{3}.\w{3}.\w{3}.\w{3}', n)
            print("IP: ", match1.group())
            match2 = re.search('\[([\w\d/:]+)', n)
            print("날짜: ", match2.group(1))
            match3 = re.search('(GET|POST)\s* (\S+)', n)
            print("뷰 페이지: ", match3.group(2))
            print('--------------------')
        except Exception as err:
            print("not found")

def test4():
    data = fileRead()
    sum = 0
    cnt = 0
    d = []
    for n in data:
        try:
            match1 = re.search('\d+$|-$', n)
            if match1.group() != '-':
                d.append(int(match1.group()))

        except Exception as err:
            print("not found")

    print("전체 전송 사이즈: ", math.fsum(d))
    print("전송 사이즈 평균: ", statistics.mean(d))
    print("전송 사이즈 표준편차: ", statistics.stdev(d))

while True:
    i = input("메뉴를 선택하시오: (8번 종료)")
    if i == '1':
        test1()
    if i == '4':
        test4()
    if i == '8':
        break
