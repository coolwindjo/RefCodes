import sqlite3

def createTable():
    try:
        sql='create table if not exists ' \
            'birth(name varchar(20),age int,birthdate varchar(20))'
        db = sqlite3.connect('birth.db')
        db.execute(sql)
        db.close()
        print("create success")
    except Exception as err:
        print("에러",err)

def insertTable( name, age, birthdate ):
    try:
        sql="insert into birth(name,age,birthdate)" \
            " values(?,?,?)"
        db = sqlite3.connect('birth.db')
        db.execute(sql, (name,age,birthdate) )
        db.commit()
        db.close()
        print("insert success")
    except Exception as err:
        print("에러",err)

def selectTable():
    try:
        sql="select * from birth"
        db = sqlite3.connect('birth.db')
        cur = db.cursor()
        cur.execute(sql)
        data = cur.fetchall()
        db.commit()
        db.close()
        return data
    except Exception as err:
        print("에러",err)
        return None
