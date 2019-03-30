#3.3 Mutable Immutable
i=10
id(i)
i=i+1
id(i) # Changed

l=[1,2,3]
id(l)
l.append(4)
id(l) # Not changed

b=True
b2=True
id(b) == id(b2) # True

s="ABCD"
s2="ABCD"
id(s) == id(s2) # True

s="한글"
s2="한글"
id(s) == id(s2) # False

s="AB CD"
s2="AB CD"
id(s) == id(s2) # False

fl=3.14
fl2=3.14
id(fl) == id(fl2) # False

x=257
y=257
id(x) == id(y) # False