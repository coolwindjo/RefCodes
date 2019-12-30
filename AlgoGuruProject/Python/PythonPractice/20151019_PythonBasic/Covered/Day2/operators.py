# 5. Operators
2 ** 3
3.14 ** 2
2 ** 0.5
3 // 2

a=3
b=2
a *= 2+b
a # 12

student_score = 95
90 <= student_score <=100 # True
lst = [1,2,"Hello world"]
lst1 = [1,2, "Hello world"]
id(lst) == id(lst1) # False
lst is lst1 # False
lst == lst1 # True
lst != lst1 # False

data = 158
mask1 = 8
data & mask1 # 8

mask2 = 1
data | mask2 # 159

mask3 = 3
mask3 = mask3 << 4
result = data & mask3
result = result >> 4
result # 1

