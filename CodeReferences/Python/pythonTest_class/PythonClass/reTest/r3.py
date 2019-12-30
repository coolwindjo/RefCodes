import re
s1 = 'apple kiwi banna'
s2= '서울가 은평구'
try:
    match = re.search('ki[vwx]i', s1)
    if (match != None): print( match.group() )
    match = re.search('ki[a-z]i', s1)
    if (match != None): print( match.group() )
    match = re.search('ki[a-z]+i', s1)
    if (match != None): print( match.group() )
    match = re.search('ki[a-zA-Z0-9_.]i', s1)
    if (match != None): print( match.group() )
    match = re.search('서울[시은가]', s2 )
    if (match != None): print( match.group() )
    match = re.search('서울[가-힣]', s2 )
    if (match != None): print( match.group() )
    match = re.search('ap+le|straw', s1 )
    if (match != None): print( match.group() )
except Exception as err:
    print('not found')


    # my = re.findall('ki[vwx]i', s1)
    # print( my)
