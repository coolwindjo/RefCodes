#함수
def fn1():
    print('hello')
    print('korea')

def hap( a,b ):
    if type(a) == int:
        return a+b
    else:
        print('wrong type')
        return None

# rst = hap( 10,20 )
# rst = hap( 10.2,20.3 )
# rst = hap( 'abc', 'def' )
rst = hap( [10,20], [30,40] )
print( rst )
# fn1()
# fn1()
# fn1()
