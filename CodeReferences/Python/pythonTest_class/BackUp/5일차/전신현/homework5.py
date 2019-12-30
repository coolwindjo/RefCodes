import csv
import re
import statistics
from collections import Counter

data = []
#ip, date, viewpage, byte
parsing_data= []

def ReadData():
    fp = open('localhost_access_log.txt')
    rd = csv.reader(fp)

    for r in rd:
        data.append(r)

    fp.close()

def SelectData():
    for idata in data:
        s = str(idata)
        s = s[2:len(s)-2]

        ip = re.search('\d{1,3}.\d{1,3}.\d{1,3}.\d{1,3}',s)
        if ip == None:
            ip = re.search('[\d:]{15}',s)
        ip = ip.group()

        date = re.search('\[([\w/:]+)', s)
        date = date.group(1)

        viewpage = re.search('(GET|POST) (\S+|)',s)
        viewpage = viewpage.group(2)

        byte = re.search('\S+$',s)
        byte = byte.group()

        parsing_data.append([ip,date,viewpage,byte])

def Menu1():
    for ii in parsing_data:
        print("ip=",ii[0], "날짜=",ii[1], "뷰페이지=", ii[2])

def Menu4():
    array = []
    for ii in parsing_data:
        if ii[3] == '-':
            array.append(int(0))
            continue
        else:
            array.append(int(ii[3]))

    print("전체전송바이트",sum(array))
    print("평균",statistics.mean(array))
    print("표준편차",statistics.stdev(array))

def Menu5():
    ipdata = []
    for ii in parsing_data:
        ipdata.append(ii[0])


    Result = Counter(ipdata)
    print("가장 많이 방문한 ip와 방문수 = ",Result.most_common(1))

def Menu6():
    ipdata = []
    for ii in parsing_data:
        ipdata.append(ii[0])

    Result = Counter(ipdata)
    print("가장 많이 방문한 ip와 방문수 Top5 = ",Result.most_common(5))

def Menu2():
    ipdata = []
    for ii in parsing_data:
        ipdata.append(ii[0])

    Result = Counter(ipdata)

    print("ip별 방문횟수 = ",Result.most_common())

def Menu3():
    viewdata = []
    for ii in parsing_data:
        viewdata.append(ii[2])

    Result = Counter(viewdata)
    print("페이지별 뷰수 = ",Result.most_common())



## main ##
ReadData()
SelectData()
# Menu1()
# Menu2()
# Menu3()
# Menu4()
# Menu5()
# Menu6()


