import csv
def csvWrite():
    fp = open('libTest/data/my.csv','w', newline='')
    wr = csv.writer(fp)
    wr.writerow( ['aa',10,20] )
    wr.writerow( ['bb',20,30] )
    wr.writerow( ['cc',40,50] )
    fp.close()
fp = open('libTest/data/my.csv')
rd = csv.reader(fp)
print( rd ) #generator
for n,k,e in rd:
    print(n,k,e)
fp.close()
