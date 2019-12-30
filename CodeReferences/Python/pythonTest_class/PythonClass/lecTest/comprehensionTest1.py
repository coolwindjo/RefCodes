my = [ n*10 for n in range(1,6) ]
print( my )
my1 = [ n*10 for n in range(1,6) if n>=3 ]
print( my1 )
# 각연봉의 세금 3.3을제한 실수령액 리스트를 구하시요
salalry =[1000,2000,3000,4000,5000]
sil = [ n*(1-0.033) for n in salalry]
print( sil )
s = { n for n in range(1,6) }
print( s )
dt =[('aa',10),('bb',20),('cc',30)]
d = { k:v for k,v in dt}
print( d )
