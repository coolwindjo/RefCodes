# -*- coding: utf-8 -*-

def Function1():
    
    a = int(input("input first num  : "))
    b = int(input("input second num : "))
    
    sum = 0;

    for i in range(a, b+1):
       sum += i;

    with open("output.txt", 'w') as f:
        f.write(str(sum))
    f.close()

    return

def main():
	
    ret = Function1()
    return

if __name__ == "__main__":
	main()