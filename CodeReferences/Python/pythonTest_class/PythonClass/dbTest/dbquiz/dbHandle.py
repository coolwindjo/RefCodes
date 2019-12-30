import sqlite3
def createTable():
    try:
        sql='create table if not exists ' \
            'grade(name varchar(20),kor int,eng int)'
        db = sqlite3.connect('grade.db')
        db.execute(sql)
        db.close()
        print("create success")
    except Exception as err:
        print("에러",err)
def insertTable( name, kor, eng ):
    try:
        sql="insert into grade(name,kor,eng)" \
            " values(?,?,?)"
        db = sqlite3.connect('grade.db')
        db.execute(sql, (name,kor,eng) )
        db.commit()
        db.close()
        print("insert success")
    except Exception as err:
        print("에러",err)
        
def selectTable():
    try:
        sql="select * from grade"
        db = sqlite3.connect('grade.db')
        cur = db.cursor()
        cur.execute(sql)
        data = cur.fetchall()
        db.commit()
        db.close()
        return data
    except Exception as err:
        print("에러",err)
        return None
