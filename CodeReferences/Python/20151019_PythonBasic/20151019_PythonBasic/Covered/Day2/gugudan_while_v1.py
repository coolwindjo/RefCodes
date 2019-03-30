output = ''
i=0
while i<11 :
    j=2
    while j < 10 :
        if i==0:
            output += "%5d단\t\t" %j
        else:
            output += "%d * %d = %d\t" %(j, i, i*j)
        j += 1
    i += 1
output += '\n'
print(output)