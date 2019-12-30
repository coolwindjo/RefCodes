i=0
while i<11 :
    j=2
    while j < 10 :
        if i==0:
            print("%5d단\t\t" %j, end='')
        else:
            print("%d * %d = %d\t" %(j, i, i*j), end='')
        j += 1
    i += 1
print()
