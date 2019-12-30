import re
s1 = 'apple  kiwi  banna'
s2 ="123-abc def-ghi 346-Abc"
s3 = '<a href="my.html">abcde</a>' \
     '<font class="a.aa" size="10">'
s4 ="aaa ab.bcd.def.kim@gmail.com xxx aa@bb.aa"
#이메일주소를 찾으시요
try:
    my = re.findall('([\w.]+)@[\w.]+', s4 )
    if (my != None): print( my )
    match = re.search('(\d{3})-([a-z]{3})', s2 )
    if (match != None): print( match.group() )
    match = re.search('href\s*="([\w.]+)"', s3 )
    if (match != None): print( match.group(0) )
    if (match != None): print( match.group(1) )
except Exception as err:
    print('not found')

# href뒤에 있는 파일명을 출력
# ex) aaa, aaa.txt, a132, aa_bc.my ...
#my.html
