import sys
# my = [n*10 for n in range(1,10000)]
# print( my )
# print( sys.getsizeof(my) )
my1 = ( n*10 for n in range(1,4) )
print( my1 )
print( sys.getsizeof(my1) )
print( list(my1) ) #[next(my1),next(my1),next(my1)]
# print( next(my1) )
# print( next(my1) ) #my1.__next__()
# print( next(my1) )
# print( next(my1) )
# print( next(my1) )#stopIteration 예외
# for n in my1:
#     print(n)

# print( next(my1) )
