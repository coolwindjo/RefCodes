from collections import Counter

my =['aa','bb','aa','aa','bb','cc']
c = Counter( my )
print( c )
print( c['aa'] )
print( c.most_common() )
print( c.most_common(2) )
