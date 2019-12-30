# 정규식 : 문자열 파싱
# (통계 분석, 로그 분석, 웹파싱, 네비게이션)...
# 반복메타 문자

import re
import statistics

match_list = []

def prob1():
    fp = open('localhost_access_log.txt', 'r')
    rd = fp.readline()
    for rd in fp:
        print('---------------------------------')
        match1 = re.search('^[\d.:]+\S', rd)
        match2 = re.search('\[([\w/:]+)', rd)
        match3 = re.search('(GET|POST) (([\w./-]+))', rd)
        print(match1.group())
        print(match2.group(1))
        print(match3.group(2))
    fp.close()

def prob4():
    fp = open('localhost_access_log.txt', 'r')
    rd = fp.readline()
    byte_list = []
    for rd in fp:
        match = re.search('[0-9]+$', rd)
        if match == None :
            byte_list.append(0)
        else :
            byte_list.append(int(match.group()))
    print("전체전송사이즈 : ", sum(byte_list))
    print("사이즈 평균 : ", statistics.mean(byte_list))
    print("사이즈 표준편차 : ", statistics.stdev(byte_list))



True_False = 'y'
while True:
    # name = input('name? : ')
    # kor = int(input('kor : '))
    # eng = int(input('eng : '))
    print("1. 전체 로그 보기")
    print("2. ip별 방문 횟수(x.x.x.x.x:x회")
    print("3. 페이지별 뷰수(ex a.htm:x회)")
    print("4. 전체전송바이트 사이즈와 평균, 표준편차")
    print("5. 가장많이 방문한 ip 와 방문수")
    print("6. 가장많이 방문한 ip 와 방문수 top 5")
    print("7. 엑셀 그래프로 저장(페이지별뷰수, ip별방문수 2개의 그래프)")

    print("메뉴를 선택하시요:")
    num = int(input())
    if num == 1:
        prob1()
    elif num == 4:
        prob4()
    else :
        break

else:
    pass

    # match1 = re.search('^[\d.:]+\S', rd)
    # match2 = re.search('\[([\w/:]+)', rd)
    # match3 = re.search('(GET|POST) (/([\w. ][^"]+))', rd)

    # print(match1.group())
    # print(match2.group(1))
    # print(match3.group(2))
