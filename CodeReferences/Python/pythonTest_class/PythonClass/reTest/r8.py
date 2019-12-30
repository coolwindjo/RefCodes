import re
s1 = 'apple kiwi banna'
try:
    reObj = re.compile('app\w+') #정규식객체 반환...
    match = reObj.search(s1)
    print( match.group() )
except Exception as err:
    print('not found')
