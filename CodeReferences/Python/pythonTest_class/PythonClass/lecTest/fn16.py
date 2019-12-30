import statistics
data1 = [10,20,30,25]
data2 = [(10,20),(70,15),(40,50)]
data3 = [{'kor':10,'eng':20},{'kor':70,'eng':15},{'kor':40,'eng':50}]

print( statistics.mean(data1) )
print( statistics.median(data1) )
print( statistics.stdev(data1) )


# print( [ n[0] for n in data2] )
# m = map( lambda v:v[0], data2)
# print( list(m) )
# print( sum( data1 ) )
# print( sum( [ n[0] for n in data2] ) )
# print( sum( map(lambda v:v[0],data2) ) )

# def mymap( func, dt):
#     return [ func(n) for n in dt]
# m = mymap(lambda v:v+2, data1)
# print( list(m) )
#
# m = map(lambda v:v+2, data1)
# print( list(m) )


# def myfilter( func, dt):
#     return ( n for n in dt if func(n) )
#
# f = myfilter( lambda v:v>=20, data1 )
# print( list(f) )


# f = filter( lambda v:v>=20, data1)
# print( list(f) )


# print( sorted( data1 ) )
# print( sorted( data2 ,key=lambda v:v[0] ) )
# print( sorted( data1, reverse=True) )
# print( sorted(data3, key=lambda v:v['eng']))

# print( max(10,20))
# print( max(10,20,30,5))
# print( max( data1 ) )
# print( max( data2, key=lambda v:v[0] )[0] )
# print( max( data3, key=lambda v:v['kor'] ) )
# print( min(data1))
# print( min( data2, key=lambda v:v[0] )[0] )
