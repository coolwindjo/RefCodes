import re
s1 = 'apple kiwi banna'
try:
    match = re.search('ki.i', s1)
    if (match != None): print( match.group() )
    match = re.search('ki..i', s1)
    if (match != None): print( match.group() )
    match = re.search('ki.{2}i', s1)
    if (match != None): print( match.group() )
    match = re.search('ki\.i', s1)
    if (match != None): print( match.group() )
    # a ,ap, app, appl, apple, apple k ,...
    match = re.search('^a', s1)
    if (match != None): print( match.group() )
    match = re.search('nna$', s1)
    if (match != None): print( match.group() )
    match = re.search('n+a$', s1)
    if (match != None): print( match.group() )
except Exception as err:
    print('not found')


