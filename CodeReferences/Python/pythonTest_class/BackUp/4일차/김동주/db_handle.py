import sqlite3


def clearTable():
    try:
        sql = "delete from member"
        db = sqlite3.connect('practice4.db')
        db.execute(sql)
        db.commit()
        db.close()
        print("delete success")
    except Exception as err:
        print("에러", err)

def createTable():
    try:
        sql = 'create table if not exists member(name varchar(20), age int, birth varchar(20))'
        db = sqlite3.connect('practice4.db')
        db.execute(sql)
        db.close()
        print("creation success")
    except Exception as err:
        print("에러", err)


def insertTable(n, a, b):
    try:
        print(n, a, b)
        sql = "insert into member(name, age, birth) values(?, ?, ?)"
        db = sqlite3.connect('practice4.db')
        db.execute(sql, (n, a, b))
        db.commit()
        db.close()
        print("insert success")
    except Exception as err:
        print("에러", err)


def selectTable():
    try:
        sql = "select * from member"
        db = sqlite3.connect('practice4.db')
        cur = db.cursor()
        cur.execute(sql)
        data = cur.fetchall()
        db.commit()
        db.close()
        return data
    except Exception as err:
        print("에러", err)
