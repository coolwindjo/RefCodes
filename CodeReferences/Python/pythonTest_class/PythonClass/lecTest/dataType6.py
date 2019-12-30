s = 'abcdefg'
#indexing
#    0123456
#    ...-3-2-1
print( s[0] )
print( s[-1] )
# 슬라이싱 [시작인덱스:끝인덱스:증가치]
# 시작인덱스<= index < 끝인덱스
print( s[1:4:1] ) #1<=index<4 1,2,3
print( s[1:4:2] ) #1,3
print( s[1:4] ) #1씩증가 기본..
print( s[:4] ) #0이 기본값 0,1,2,3
print( s[2:] ) #끝까지
print( s[0:-1] )
print( s[-1:-4:-1] ) #-1-2-3
print( s[ :-4:-1] ) #-1-2-3


















