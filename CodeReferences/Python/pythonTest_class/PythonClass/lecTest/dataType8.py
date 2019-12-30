s = b'abc'
print( s )
print(type(s))
print( s[0] )
print( chr( s[0] ) )
print( ord('A') )


#통신 octet(8bit 1byte)
# python  ----write(send)-----> 장치,호스트
# str --> bytes로 변환
#python <------read(receive)------장치,호스트
# bytes -->str로변환

# s1 ='def'
# str ==> bytes 로변환
# s1 = s1.encode(encoding='utf-8')
# print( s1 )
# print( type(s1) )
# s2 =b'ghi'
# s2 = s2.decode(encoding='utf-8')
# print( s2 )
# print( type(s2) )
