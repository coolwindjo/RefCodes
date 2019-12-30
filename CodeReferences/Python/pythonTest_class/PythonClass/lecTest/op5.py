a=5
b=None
# and( 모두 True True)
# rst = a>0 and a==0
#or( 모두 False False)
# rst = a>0 or a==0
rst = not 'abc'#''#[10]#[] #10#0 #a>0
print( rst )
# False: 0, None, '',[],(),{}
# True :0이 아닌정수실수(1,11,3.14),
# 'ab',[10,20],(10,),{'a':10}
print("========")
# 요소 in 복합데이터타입
s = 'hello korea'
my = [10,20,30]
d ={'aa':10,'bb':20}
print( 'llo' in s)
print( 20 in my )
print( 100 not in my )
print( 'aa' in d ) #d.keys()
print( 10 in d.values() )








