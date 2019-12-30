n = 10
n = str(n)
print(n, type(n))
s = '100'
s = int(s)
print(s, type(s))
f = '3.14'
f = float(f)
print(f, type(f))

t = (1,2,3)
t = list(t)
print(t, type(t))

my = [11,22,33]
my = tuple(my)
print(my, type(my))

d={'a':10,'b':20}
d = list(d)
print(d, type(d))
print("======")
my = [11,22,33]
e = enumerate( my )
my = dict( e )
print(my, type(my))

my1=['a','b','c']
my2=[10,20,30]
z = zip(my1,my2)
for n1,n2 in z:
    print(n1,n2)
# dd = dict(z)
# print( dd )
# myz = list( z )
# print( myz )
# myz1 = list( z )
# print( myz1 )












