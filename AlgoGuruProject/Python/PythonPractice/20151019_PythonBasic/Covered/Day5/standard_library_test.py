# -*- coding: utf-8 -*- 
import os
import time
import sys
import datetime

def get_time_gap(*str_sec):
    if (len(str_sec) == 0):
        str_sec = input("Enter amount of time in seconds:")

    t1 = time.time( )   # get timestamp
    time.sleep(int(str_sec[0]))
    
    t2 = time.time( )
    
    time_gap = t2 - t1

    print("Time gap:", time_gap)
    return

def mk_file():
    fp = open("hello.txt", 'a+')
    print('Hello world', file = fp)
    fp.write("Hello")
    fp.close()
    return "hello.txt"

# main function
def main():
    #
    d = datetime.date(2015,10, 23)
    print(time.time())
    print(datetime.date.fromtimestamp(time.time()))
    print(d.toordinal())
    print(datetime.date.fromordinal(d.toordinal()))

    #
    print(time.gmtime())
    now = time.localtime()
    print(now)
    print(now.tm_year, now.tm_mon, now.tm_mday, sep=' ')
    print(time.asctime())
    print(time.mktime(time.localtime()))
    print(time.strftime("%B %dth %A %I: %M", time.localtime()))


    #
    print(sys.copyright)
    print(sys.version)
    print(sys.getwindowsversion())

    #
    print(os.name)
    print(os.getcwd())
    print(os.path.join(os.getcwd(),'test'))
    dir_list = os.listdir()
    print(dir_list)
    os.mkdir(os.path.join(os.getcwd(), 'test'))
    print(os.listdir())
    os.chdir(os.path.join(os.getcwd(), 'test'))
    file_name = mk_file()
    print(os.listdir())
    os.remove(os.path.join(os.getcwd(), file_name))
    print(os.listdir())
    os.chdir(os.path.join(os.getcwd(), '..'))
    os.rmdir(os.path.join(os.getcwd(), 'test'))
    print(os.getcwd())
    os.system("dir")
    print(os.getenv("PYTHON35_HOME"))

    #
    print(time.time)
    t = time.localtime()
    print(time.asctime())
    get_time_gap(5)
    print(time.asctime(t))

    
    return

if __name__ == "__main__":
    main()