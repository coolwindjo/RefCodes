a=5
# rst = 100 if a>0 else 200
# rst = [200,100][ a>0 ]
rst = {False:200, True:100}[a>0]
print( rst )
# 70점이상이면 '합격' 아니면 '불합격'
jumsu = 80
print( '합격' if jumsu>=70 else '불합격')
print( ['불합격', '합격'][ jumsu>=70 ] )
