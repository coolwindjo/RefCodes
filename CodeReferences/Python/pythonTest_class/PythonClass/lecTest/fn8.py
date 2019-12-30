# my = [10,20,30]
# my1 = my
# my = 'abc'
# my1 = 'abc'
def fn():
    my = [10,20,30]
    print("myid", id(my))
    print( my )
    return my

rst = fn()
print( id(rst))
print( rst )






