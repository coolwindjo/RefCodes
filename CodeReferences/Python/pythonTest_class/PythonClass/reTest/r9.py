import re
s1 ='aaa-bbb#ccc.ddd eee'
s2 = 'i like apple like application'
def fn(m):
    print('m=', m)
    my = m.group()
    if my=='apple':
        return 'aaa'
    else:
        return 'bbb'

nCnt=-1
myList = ['hello', 'korea']
def fn1(m):
    global nCnt
    nCnt+=1
    return m.group()+myList[nCnt]
try:
    s = re.sub('ap\w+','love',s2)
    if (s != None): print( s )
    s = re.sub('ap\w+', fn, s2)
    if (s != None): print( s )
    s = re.sub('ap\w+',lambda m:'aaa' if m.group()=='apple' else 'bbb',s2 )
    if (s != None): print( s )
    s = re.sub('ap\w+', fn1, s2)
    print( s )
except Exception as err:
    print('not found')





    # my = re.split('[ #.-]', s1 )
    # print( my )
