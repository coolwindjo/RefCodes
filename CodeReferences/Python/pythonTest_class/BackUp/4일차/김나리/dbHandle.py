import sqlite3

def createTable():
    try:
        sql = "create table if not exists person(name varchar(20), age int, birth varchar(20))"
        db = sqlite3.connect('personal_info.db')
        db.execute(sql)
        db.close()
        # print("create success")
    except Exception as err:
        print("에러",err)

def insertTable(data):
    try:
        sql = "insert into person values(?,?,?)" 
        db = sqlite3.connect('personal_info.db')
        db.execute(sql,data)
        db.commit()
        db.close()
        # print("insert success")
    except Exception as err:
        print("에러",err)

