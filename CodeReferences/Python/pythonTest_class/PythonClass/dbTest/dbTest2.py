import sqlite3
# https://www.w3schools.com/sql/
def deleteTable():
    try:
        # sql="delete from student where name='이이'"
        sql="delete from student where name=?"
        db = sqlite3.connect('test.db')
        db.execute(sql, ('이이',) )
        db.commit()
        db.close()
        print("delete success")
    except Exception as err:
        print("에러",err)
def updateTable():
    try:
        # sql="update student set name='이순신1',age=32 " \
        #     "where name='이순신'"
        sql="update student set name=?,age=? " \
            "where name=?"
        db = sqlite3.connect('test.db')
        db.execute(sql,('이순신2',33,'이순신1'))
        db.commit()
        db.close()
        print("update success")
    except Exception as err:
        print("에러",err)
def selectTable():
    try:
        sql="select * from student"
        db = sqlite3.connect('test.db')
        cur = db.cursor()
        cur.execute(sql)
        data = cur.fetchall()
        db.commit()
        db.close()
        print(data)
        for n,a,b in data:
            print(n,a,b)
    except Exception as err:
        print("에러",err)
def selectTable1():
    try:
        sql="select * from student"
        db = sqlite3.connect('test.db')
        cur = db.cursor()
        cur.execute(sql)
        for c in cur:
            print( c )
        db.commit()
        db.close()
    except Exception as err:
        print("에러",err)
def updateTable1():
    try:
        sql="update student set name=?,age=? " \
            "where name=?"
        db = sqlite3.connect('test.db')
        cur = db.cursor()
        cur.execute(sql,('이순신3',34,'이순신2'))
        print("수정갯수:", cur.rowcount )
        db.commit()
        db.close()
        print("update success")
    except Exception as err:
        print("에러",err)
def selectTable2():
    try:
        # sql="select * from student"
        # sql="select * from student where age=30"
        # sql="select * from student where age in(30,50)"
        # sql="select * from student " \
        #     "where age=30 or name='김철수'"
        # sql="select * from student " \
        #     "where age=30 and name='임꺽정'"
        # sql="select * from student " \
        #     "where age between 30 and 50" #30<=age<=50
        # sql="select * from student " \
        #     "where name like '%철%'"
        # sql="select * from student order by name"
        # sql="select * from student order by name desc"
        # sql="select * from student limit 2"
        sql="select * from student " \
            "order by age desc limit 2"
        db = sqlite3.connect('dbTest/test.db')
        cur = db.cursor()
        cur.execute(sql)
        data = cur.fetchall()
        db.commit()
        db.close()
        for n,a,b in data:
            print(n,a,b)
    except Exception as err:
        print("에러",err)
#집계 : count, avg, sum, max, min
def selectTable3():
    try:
        # sql="select count(age) from student"
        # sql="select count(*) from student"
        # sql="select sum(age) from student"
        # sql="select avg(age) from student"
        # sql="select max(age) from student"
        # sql="select min(age) from student"
        sql="select sum(age),avg(age)" \
            " from student"
        db = sqlite3.connect('dbTest/test.db')
        cur = db.cursor()
        cur.execute(sql)
        data = cur.fetchone()
        print( data )
        db.commit()
        db.close()
    except Exception as err:
        print("에러",err)
selectTable3()









