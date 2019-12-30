#참조계수기법(RC)
#Reference Count

my = [10,20,30]
# my1 = my #shallow copy
# my1 = [10,20,30]
my1 = my.copy() #deep copy
print( id(my), id(my1) )
my1[0] = 100
print( my )
print( my1)

