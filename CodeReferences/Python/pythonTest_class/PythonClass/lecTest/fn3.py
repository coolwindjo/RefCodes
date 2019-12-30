# (가변인자:호출값 갯수에 제한없음)
def fn( *args ):
    print( args)
    for n in args:
        print(n)

def circles( *rs ):
    for r in rs:
        print(r**2*3.14)
a=10
b=3.14
c='abc'
s='a={0} b={1} c={2}'.format(a,b,c)
print(s )
s1 = 'a=%d b=%f c=%s'%(a,b,c)
s2 = f'a={a} b={b} c={c}'
t = (11,22,33)
s3 = '{}-{}-{}'.format( *t )
print(s3)
# fn( *(1,2,3) ) #unpacking
# fn(1,2,3)

# a = (10,)
# a = (10+2)*2
# circles(1,2,3,4)
# fn(10,20,30)
# fn(1,2,3,4,5)




