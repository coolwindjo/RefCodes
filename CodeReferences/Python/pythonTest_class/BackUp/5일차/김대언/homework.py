from collections import Counter
import statistics
# 1. 전체 로그보기(ip: .. 날짜: .. 뷰페이지: )
logData = []
def makeData():
    fLog = open("localhost_access_log.txt", 'r')
    for line in fLog:
        splited = line.split(' ')
        ip = splited[0]
        date = splited[3] + splited[4]
        vPage = splited[6]
        size = splited[9].split('\n')[0]
        if size == '-':
            size = 0
        logData.append({'ip': ip, 'date': date, 'vPage': vPage, 'size': int(size)})
    fLog.close()

makeData()
print('<<<<1번>>>>')
for n in logData:
    print('ip:', n.get('ip', 'none'))
    print('날짜:', n.get('date', 'none'))
    print('뷰페이지:', n.get('vPage', 'none'))
    print('전송바이트:', n.get('size', 0))
    print('-'*40)

print('\n<<<<2번>>>>')
cIp = Counter([n.get('ip', 'none') for n in logData])
print(cIp.most_common())

print('\n<<<<3번>>>>')
c3 = Counter([n.get('vPage', 'none') for n in logData])
print(c3.most_common())

print('\n<<<<4번>>>>')
print('전체전송바이트 사이즈:', sum([n.get('size', 0) for n in logData]))
print('평균:', statistics.mean([n.get('size', 0) for n in logData]))
print('표준편차', statistics.stdev([n.get('size', 0) for n in logData]))

print('\n<<<<5번>>>>')
print(cIp.most_common(1))

print('\n<<<<6번>>>>')
print(cIp.most_common(5))
