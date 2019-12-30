import sqlite3
def createTable():
    try:
        sql='create table if not exists ' \
            'grade(name varchar(20),kor int,eng int)'
        db = sqlite3.connect('dbTest/grade.db')
        db.execute(sql)
        db.close()
        print("create success")
    except Exception as err:
        print("에러",err)
def insertTable( name, kor, eng ):
    try:
        sql="insert into grade(name,kor,eng)" \
            " values(?,?,?)"
        db = sqlite3.connect('dbTest/grade.db')
        db.execute(sql, (name,kor,eng) )
        db.commit()
        db.close()
        print("insert success")
    except Exception as err:
        print("에러",err)

def selectTable():
    try:
        sql="select * from grade"
        db = sqlite3.connect('dbTest/grade.db')
        cur = db.cursor()
        cur.execute(sql)
        data = cur.fetchall()
        db.commit()
        db.close()
        return data
    except Exception as err:
        print("에러",err)
        return None

createTable()
while True:
    name = input('이름:')
    kor = int( input('국어:') )
    eng = int( input('영어:') )
    insertTable(name,kor,eng)
    yn = input("계속입력(y/n):")
    if yn=='n':
        break
for n,k,e in selectTable():
    print(n,k,e)

#데이터베이스:데이터 저장소

#관계형데이터베이스(sql)
#1) 대형:오라클, DB2,사이베이스,인포믹스
#2) 중형:ms sqlserver, maria , mysql
#3) 소형(stand alone): sqlite, access

#비관계형데이터베이스( no sql):빅데이터
#hbase, 몽고db, 카산드라, 레디스, 아마존 카우치DB 등등











