for item2 in range(2, 10):
    print("%5d단" % (item2), end="\t\t")
print("\n")
for item1 in range(1, 11):
    for item2 in range(2, 10):
        print("%d * %d = %d" %(item2, item1, item1*item2), end="\t")
    print("")
