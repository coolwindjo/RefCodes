import re
s1 = 'apple kiwi banna application'
try:
    matchs = re.finditer('app\w+',s1)
    if (matchs != None): print( matchs ) #generator
    for m in matchs:
        print( m.group() )
except Exception as err:
    print('not found')
