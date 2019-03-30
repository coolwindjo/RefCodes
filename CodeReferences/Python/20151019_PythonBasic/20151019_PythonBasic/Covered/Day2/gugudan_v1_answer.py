output = ''

for i in range(0,11):
    for j in range(2,10):
        if i==0:
            output += "%5d단\t\t" %j
        else:
            output += "%d * %d = %d\t" %(j, i, i*j)
    output += '\n'
print(output)