data1 = [10,20,30,25]
data2 = [(10,20),(70,15),(40,50)] #국어, 영어
data3 = [{'kor':10,'eng':20},{'kor':70,'eng':15},{'kor':40,'eng':50}]
def mymax(dt, key= lambda v:v):
    mx = None
    for n in dt:
        if mx==None  or key(n)>key(mx):
            mx = n
    return mx
mx = mymax( data1 ) #임시함수.
print( mx )

# mx = mymax( data2, lambda v:v[0] ) #임시함수.
# print( mx )

