import sqlite3

def createTable():
    try:
        sql='create table if not exists ' \
            'person(name varchar(20), age int, birth date)'
        db = sqlite3.connect('person.db')
        db.execute(sql)
        db.close()
        print("create success")
    except Exception as err:
        print("에러",err)

def insertTable(name, age, birth):
    try:
        sql = "insert into person(name,age,birth)" \
              " values(?,?,?)"
        db = sqlite3.connect('person.db')
        db.execute(sql, (name, age, birth))
        db.commit()
        db.close()
        print("insert success")
    except Exception as err:
        print("에러", err)


def selectTable():
    try:
        sql = "select * from person"
        db = sqlite3.connect('person.db')
        cur = db.cursor()
        cur.execute(sql)
        data = cur.fetchall()
        db.commit()
        db.close()
        return data
    except Exception as err:
        print("에러", err)
        return None

