import re
#1. ip address
#2. 요청시간:01/Apr/2016:12:39:00
#3. 요청문서: GET,POST /bg-nav.png
#4. 바이사이즈..
s1 = '192.168.123.240 - - [01/Apr/2016:12:39:00 +0900] "GET /bg-nav.png HTTP/1.1" 200 1401'
try:
    match = re.search('\d{1,3}.\d{3}.\d{3}.\d{3}', s1 )
    if (match != None): print( match.group() )
    match = re.search('\[([\w/:]+)', s1 )
    if (match != None): print( match.group() )
    match = re.search('(GET|POST) (\S+)', s1 )
    if (match != None): print( match.group() )
    match = re.search('\d+$', s1 )
    if (match != None): print( match.group() )
except Exception as err:
    print('not found')

