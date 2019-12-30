import sqlite3
import re
import csv
from statistics import mean,stdev
from collections import Counter
#
# def createTable():
#     try:
#         sql='create table if not exists ' \
#             'log(ip varchar(20), date varchar(40),type varchar(10),page varchar(10),ext varchar(20))'
#         db = sqlite3.connect('test.db')
#         db.execute(sql)
#         db.close()
#         print("create success")
#     except Exception as err:
#         print("에러",err)
#
# def insertTable():
#     try:
#         sql="insert into log(ip varchar(20), date varchar(40),type varchar(10),page varchar(10),ext varchar(20))" \
#             " values(?,?,?,?,?)"
#         db = sqlite3.connect('test.db')
#         db.execute(sql, ('이순신',30,'1989-11-12') )
#         db.commit()
#         db.close()
#         print("insert success")
#     except Exception as err:
#         print("에러",err)
def readFile1():
    fp =open('localhost_access_log.txt','r')
    for rd in fp:
        # print(rd)
        try:
            match=re.search('0:0:0:0:0:0:0:1|[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}',rd)
            print( "ip:",match.group() )
            match=re.search('[0-9]{2}/[A-Za-z]+/[0-9]{4}:[0-9]{2}:[0-9]{2}:[0-9]{2} \++[0-9]{4}',rd)
            print("날짜:", match.group() )
            match=re.search('/[a-zA-Z0-9]+.[a-zA-Z0-9]+ | / HTTP/1.1',rd)
            print("뷰페이지:", match.group() )
            print("")
        except Exception as err:
            print('not found')

    fp.close()

def num4():
    fp =open('localhost_access_log.txt','r')
    cnt=int(0)
    sum=int(0)
    data=[]
    for rd in fp:
        cnt+=1
        try:
            match=re.search('(HTTP/1.1" )[0-9]+ (-|[0-9]+)',rd)
            # print("뷰페이지:", match.group(2) )
            if(match.group(2)=='-'):
                data.append(int(0))
            else:
                sum+=int(match.group(2))
                data.append(int(match.group(2)))
        except Exception as err:
            print('not found')
    # print(data)
    print("전체전송바이트:",sum)
    print('소계평균',mean( [ n for n in data] ) )
    print('표준편차',stdev( [ n for n in data] ))
    fp.close()
def howIP():
    fp =open('localhost_access_log.txt','r')
    data=[]
    for rd in fp:

        try:
            match=re.search('0:0:0:0:0:0:0:1|[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}',rd)
            # print(match.group())
            data.append(match.group())
        except Exception as err:
            print('not found')
    c=Counter(data)
    print(c)
    fp.close()
def howIP5():
    fp =open('localhost_access_log.txt','r')
    data=[]
    for rd in fp:

        try:
            match=re.search('0:0:0:0:0:0:0:1|[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}',rd)
            # print(match.group())
            data.append(match.group())
        except Exception as err:
            print('not found')
    c=Counter(data)
    print(c.most_common(1))
    fp.close()
def howIP6():
    fp =open('localhost_access_log.txt','r')
    data=[]
    for rd in fp:

        try:
            match=re.search('0:0:0:0:0:0:0:1|[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}',rd)
            # print(match.group())
            data.append(match.group())
        except Exception as err:
            print('not found')
    c=Counter(data)
    print(c.most_common(6))
    fp.close()
def howSite():
    fp =open('localhost_access_log.txt','r')
    data=[]
    for rd in fp:

        try:
            match=re.search('/[a-zA-Z0-9]+.[a-zA-Z0-9]+ | / HTTP/1.1',rd)
            # print("뷰페이지:", match.group() )
            data.append(match.group())
        except Exception as err:
           pass
    c=Counter(data)
    print(c)
    fp.close()

menu = {1:readFile1,2:howIP,3:howSite, 4:num4,5:howIP5,6:howIP6,0:exit}
while True:
    nSel = int( input('메뉴를 선택하시오:') )
    menu[nSel]()
