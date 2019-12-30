import sqlite3

def createTable():
    try:
        sql = 'create table if not exists '\
            'people(name varchar(20), age int, birth varchar(20))'
        db = sqlite3.connect('people.db')
        db.execute(sql)
        db.close()
        print("create success")

    except Exception as err:
        print("에러",err)

def insertTable(name,age,birth):
    try:
        sql = 'insert into people(name,age,birth) values(?,?,?)'
        db = sqlite3.connect('people.db')
        db.execute(sql,(name,age,birth))
        db.commit()
        db.close()
        print("insert success")

    except Exception as err:
        print("에러",err)

def selectTable():
    try:
        sql = "select * from people"
        db = sqlite3.connect('people.db')
        cur = db.cursor()
        cur.execute(sql)
        data = cur.fetchall()
        db.commit()
        db.close()
        return data
        print("select success")

    except Exception as err:
        print("에러",err)
