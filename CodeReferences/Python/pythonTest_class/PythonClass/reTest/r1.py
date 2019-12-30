#정규식: 문자열파싱
# ( 통계분석, 로그분석, 웹파싱, 네비게이션)...
import re
s1 = 'applle kiwi  banna'
try:
    match = re.search('ap*le', s1)
    if (match != None): print( match.group() )
    match = re.search('ap+le', s1)
    if (match != None): print( match.group() )
    match = re.search('ap?le', s1)
    if (match != None): print( match.group() )
    match = re.search('ap{2}le', s1)
    if (match != None): print( match.group() )
    match = re.search('ap{2,4}le', s1)##2,3,4
    if (match != None): print( match.group() )
    match = re.search('ap{2,4}l{1,3}e', s1)##2,3,4
    if (match != None): print( match.group() )
except Exception as err:
    print('not found')


    # my = re.findall('ap?le', s1)
    # print( my)



# match = re.search('apple', s1)
# if match:
#     print( match.group() )
# else:
#     print('not found')

