import pickle
def obWrite():
    data = [('홍길동',20),('이순신',20)]
    fp = open('libTest/data/ob.txt','wb')
    pickle.dump(data, fp)
    fp.close()
def obRead():
    fp = open('libTest/data/ob.txt','rb')
    my = pickle.load(fp)
    fp.close()
    print( my )
    for n in my:
        print(n)
obWrite()
obRead()
