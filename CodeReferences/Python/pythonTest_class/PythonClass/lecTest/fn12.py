data1 = [10,20,30,25]
data2 = [(10,20),(70,15),(40,50)] #국어, 영어
data3 = [{'kor':10,'eng':20},
         {'kor':70,'eng':15},
         {'kor':40,'eng':50}]
def mymax(dt):
    mx = None
    for n in dt:
        # if mx==None  or n>mx:
        # if mx==None  or n[0]>mx[0]:
        # if mx==None  or n[1]>mx[1]:
        if mx==None  or n['kor']>mx['kor']:
            mx = n
    return mx
mx = mymax( data3 )
print( mx )

# mx = mymax( data2 )
# print( mx )

# mx = mymax( data1 )
# print( mx )
