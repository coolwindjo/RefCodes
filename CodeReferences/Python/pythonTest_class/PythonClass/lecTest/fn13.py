data1 = [10,20,30,25]
data2 = [(10,20),(70,15),(40,50)] #국어, 영어
data3 = [{'kor':10,'eng':20},{'kor':70,'eng':15},{'kor':40,'eng':50}]
def vfn(v):
    return v
def tfn(v):
    return v[0]
def dfn(v):
    return v['kor']
def mymax(dt, key):
    mx = None
    for n in dt:
        if mx==None  or key(n)>key(mx):
            mx = n
    return mx
mx = mymax( data3, dfn )
print( mx )
# mx = mymax( data2, tfn )
# print( mx )
# mx = mymax( data1, vfn )
# print( mx )

# mx = mymax( data2 )
# print( mx )

# mx = mymax( data1 )
# print( mx )
