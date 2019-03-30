import copy

def add_one(num1, lst1):                  
    num1 = num1 + 1
    temp_lst = copy.deepcopy(lst1)
    temp_lst.append(1)                        

num = 1
lst = [1, 2, "Hello World"]
print(num, lst)                            

add_one(num, lst)
print(num, lst)
