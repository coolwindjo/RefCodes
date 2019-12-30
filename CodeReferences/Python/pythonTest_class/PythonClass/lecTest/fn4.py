#정의되지않은 인자
def fn(**kwargs):
    print( kwargs)

d ={'name':'이순신','age':30}
fn( a=10,b=20,c=30)
fn( name='홍길동', age=20 )
fn( **d ) #dict unpack
s = '{aa} {bb}'.format(aa=10, bb=20)
print( s )
s1 = '이름:{name} 나이:{age}'.format(**d)
print(s1)
