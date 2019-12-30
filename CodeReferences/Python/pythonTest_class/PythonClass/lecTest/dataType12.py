d = {'aa':10,'bb':20,'cc':30}
d['aa'] = 100 #키가있으면 수정
d['dd'] = 40 #키가 없으면 추가..
print( d.keys() )
print( d.values() )
print( d.items())
print( d.get('ff',1000)) # d['aa']
d.pop('bb')
print( d )
print( type(d) )
print( d['aa'] )
