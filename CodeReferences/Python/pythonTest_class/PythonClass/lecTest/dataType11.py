#중복데이터제거
#집합연산
s = {10,20,30,40,50,20,20}
# s.add(60)
# s.add(70)
# s.remove(30)
# print(s)
# print(type(s))
# print( s[0] )#X
s1 = {10,20,30}
s2 = {20,30,40,50}
print( s1 & s2 ) #교집합
print( s1.intersection(s2))
print( s1 | s2 ) #합집합
print( s1.union(s2))
print( s1-s2 )
print( s1.difference(s2))












