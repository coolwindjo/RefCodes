# Copy
x = [1,2,3]
lst = [1,2,x]
lst1 = [1,2,x]
id(lst) == id(lst1) # False
lst, lst1
id(lst[2]) == id(lst1[2]) # True

lst1[2][1] = 3
lst, lst1

# Deep copy
#from copy import copy, deepcopy
import copy

x = [1,2,3]
lst = [1,2,x]
#lst1 = deepcopy(lst)
lst = copy.deepcopy(lst)

id(lst) == id(lst1) # False
id(lst[2]) == id(lst1[2]) # False

lst1[2][1] = 3
lst , lst1