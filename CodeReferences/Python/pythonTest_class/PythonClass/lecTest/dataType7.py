s1 = '  abc  '
s2 = '###abc###'
s3 = 'abc def ghi'
s4 = 'abc-def-ghi'
s5 ='i like python like program'
#문자열 좌우화이트스페이스(스페이스,\n,\t,\r)
print(s1.strip() )
print( s2.strip('#'))
# 화이트스페이스기준으로 분리
print( s3.split() )
print( s4.split('-') )
print( s5.replace('like','love'))
