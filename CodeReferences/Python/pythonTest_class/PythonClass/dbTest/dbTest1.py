import sqlite3

# test.db가있으면 접속
# 없으면 생성후 접속
# https://sqlitebrowser.org/
def createTable():
    try:
        sql='create table if not exists ' \
            'student(name varchar(20), age int, birth date)'
        db = sqlite3.connect('dbTest/test.db')
        db.execute(sql)
        db.close()
        print("create success")
    except Exception as err:
        print("에러",err)
#insert, delete, update : commit(명령확정), rollback(명령취소)
def insertTable():
    try:
        sql="insert into student(name, age,birth)" \
            " values('홍길동',20,'1999-10-12')"
        db = sqlite3.connect('dbTest/test.db')
        db.execute(sql)
        db.commit()
        db.close()
        print("insert success")
    except Exception as err:
        print("에러",err)
def insertTable1():
    try:
        sql="insert into student(name, age,birth)" \
            " values(?,?,?)"
        db = sqlite3.connect('dbTest/test.db')
        db.execute(sql, ('이순신',30,'1989-11-12') )
        db.commit()
        db.close()
        print("insert success")
    except Exception as err:
        print("에러",err)
def insertTable2():
    try:
        sql="insert into student(name, age,birth)" \
            " values(?,?,?)"
        db = sqlite3.connect('dbTest/test.db')
        data=[('임꺽정',30,'1989-04-12'),
              ('이이',40,'1979-05-12'),
              ('김철수',50,'1969-06-12'),
              ('박철남',60,'1959-07-12')]
        db.executemany(sql,  data )
        db.commit()
        db.close()
        print("insert success")
    except Exception as err:
        print("에러",err)
insertTable2()



