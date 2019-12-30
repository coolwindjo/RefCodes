import sys
import re
import statistics
from collections import Counter

fp = open('localhost_access_log.txt')

ret_list  = []
cnt = 0
for item in fp :

    match = re.search('\d{1,3}.\d{1,3}.\d{1,3}.\d{1,3}', item)
    ip_addr = match.group()

    match = re.search('\[([\w\d/:]+)', item)

    day_var = match.group(1)

    match = re.search('(GET|POST)(.+)HTTP',item)

    view_page = match.group(2)

    tmp_t = (ip_addr, day_var,view_page)
    ret_list.append(tmp_t)

print('1. 전체 로그보기(ip: .. 날짜: .. 뷰페이지: )  ')

for item in ret_list :
    print('ip: ', item[0])
    print('날짜: ', item[1])
    print('뷰페이지: ', item[2])
    print('------------------------------')



fp = open('localhost_access_log.txt')

ip_list = []
for item in fp :

    match = re.search('\d{1,3}.\d{1,3}.\d{1,3}.\d{1,3}', item)
    ip_addr = match.group()
    ip_list.append(ip_addr)


# print(ip_list)
ret_cnt = Counter(ip_list)
# print(ret_cnt)

print('-'*40)
print('2. ip별 방문 횟수( 000.000.000.000:x회)')


for key, value in ret_cnt.items() :
    print('IP :', key, '방문횟수: ',  value)

print('-'*40)
print('5. 가장많이 방문한 ip 와 방문수')
print('가장 많이 방문한 IP : ', ret_cnt.most_common(1)[0][0], '방문횟수:' ,ret_cnt.most_common(1)[0][1] )

print('-'*40)
print('6. 가장많이 방문한 ip 와 방문수 top5')
top_5 = ret_cnt.most_common(5)
# print(top_5)

for idx, item in enumerate(top_5) :
    print(idx, '많이 방문한 ip(',idx, ')  :' , item[0],  '방문횟수 :', item[1] )



print('********************************************')
print('4. 전체전송바이트 사이즈 와 평균, 표준편차  ')

fp = open('localhost_access_log.txt')

ret_list2 = []
for item in fp :
    # print(item)
    trans_byte = item.split(' ')[-1].strip('\n')
    # print(trans_byte)
    ret_list2.append(trans_byte)


# print('******************')
# print(ret_list2)

ret_final  =  []
for item in ret_list2 :
    if item == '-' :
        ret_final.append(0)
    else :
        ret_final.append(int(item))


# print(ret_final)
ret_tsize = sum(ret_final)
ret_mean  = statistics.mean(ret_final)
ret_stdev = statistics.stdev(ret_final)


print('전체전송바이트 사이즈: ', ret_tsize)
print('평균                 : ', ret_mean)
print('표준편차             : ', ret_stdev)


print('-'*50)
print('3. 페이지별 뷰수(ex /a.htm:x회 )')


fp = open('localhost_access_log.txt')


view_list  = []

for item in fp :

    match = re.search('(GET|POST)(.+)HTTP',item)

    view_page = match.group(2)
    view_list.append(view_page)


# print(view_list)

ret_cnt = Counter(view_list)
# print(ret_cnt)


for key, value in ret_cnt.items() :
    print('페이지 :', key, '뷰수: ',  value)



