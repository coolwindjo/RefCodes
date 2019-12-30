# if switch(X) -->dict
a=5
if a>0:
    print('크다')
elif a==0:
    print('같다')
else:
    print("작다")
print('hello')
# 하나의 점수를 읽어
# 90~100 'A'
# 80~89 'B'
# 70~79 'C'
# 60~69 'D'
# 나머지 'F'
jumsu = int( input("점수:") )
if 90<= jumsu <=100:
    print('A')
elif 80<= jumsu <=89:
    print('B')
elif 70<= jumsu <=79:
    print('C')
elif 60<= jumsu <=69:
    print('D')
else:
    print('F')






