FILENAME = 'libTest/data/test.txt'

def writeFile():
    fp = open(FILENAME,'w')
    # print( type(fp))
    fp.write('hello')
    fp.close()
def readFile():
    fp =open(FILENAME,'r')
    rd = fp.read()
    fp.close()
    print(rd)
#shift + tab
writeFile()
readFile()


def readWith():
    with open(FILENAME,'r') as fp:
        rd = fp.read()
        print( fp.closed )
        print(rd)
    print( fp.closed )

readWith()


def writeFileTellSeek():
    fp = open(FILENAME,'w')
    print( fp.tell() )
    fp.write('hello')
    fp.seek(2)
    print( fp.tell() )
    fp.write('korea')
    print( fp.tell() )
    fp.close()

def readFile1():
    fp =open(FILENAME,'r')
    print( fp.tell() )
    rd = fp.read(3)
    print( fp.tell() )
    print(rd)
    rd = fp.read(3)
    print( fp.tell() )
    print(rd)
    fp.close()
def readFile2():
    fp =open(FILENAME,'r')
    while True:
        rd = fp.read(3)
        # if rd=='':
        if not rd:
            break
        print(rd)
    fp.close()
def readFile3():
    fp =open(FILENAME,'r')
    for rd in fp:
        print(rd)
    # rd = fp.readline()
    # print(rd)
    # rd = fp.readline()
    # print(rd)
    fp.close()

writeFileTellSeek()
readFile1()
readFile2()
readFile3()

def writeFile1():
    fp = open(FILENAME,'w')
    fp.write('abc\ndef\nghi')
    fp.close()
def readFile4():
    fp =open(FILENAME,'r')
    rd = fp.readlines()
    print( rd)
    rd = [ n.strip() for n in rd]
    print( rd)
    fp.close()

writeFile1()
readFile4()

#w text mode 10 --> 13,10
def writeFile5():
    fp = open(FILENAME,'w')
    fp.write('kor\nea')
    fp.close()
#r text mode 13,10 --> 10(\n)
# 객체,이미지, 사운드, 동영상.원코드 유지
def readFile5():
    fp =open(FILENAME,'r')
    rd = fp.read()
    print( len(rd))
    fp.close()
    print(rd)

writeFile5()
readFile5()
