#shelve dict 와 멤버가 동일...
#dict 메모리, shelve ??.dat(sqlite db엔진)
import shelve
def shWrite():
    sh = shelve.open('libTest/data/my')
    sh['aa'] = 10
    sh['bb'] = 20
    sh['name'] ='홍길동'
    sh['age'] =20
    sh['data'] =[(10,20),(30,40)]
    sh.close()

shWrite()
sh = shelve.open('libTest/data/my')
print( sh['aa'] )
print( sh['bb'] )
print( sh['name'] )
print( sh['age'] )
print( sh['data'] )
sh.pop('bb')
for n in sh:
    print( n )
print("===========")
for n in sh.values():
    print(n)

# d = {} #dict()
# d['aa'] = 10
# d['bb'] = 20
# print(d)




