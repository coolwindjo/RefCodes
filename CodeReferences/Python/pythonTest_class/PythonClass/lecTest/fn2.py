def fn1():
    return 10,20

def shape(r, h, w ):
    return r**2*3.14, h*w

def fn2(a,b):
    print(a,b)

def fn3(x=10,y=20): #디폴트인자
    print(x,y)

# ctrl + p, ctrl+q
print(10,20, sep='-')
print( 'hello', end=' ' )
print('korea')
# fn3()
# fn3(100)
# fn3(100,200)
# fn3(y=1000)


# fn2(10,20)
# fn2(b=100,a=200) #명시적호출

# rst = shape(3,10,20)
# print(rst )

# rst = fn1()
# print(rst)
# a,b = fn1()
# print(a,b)
