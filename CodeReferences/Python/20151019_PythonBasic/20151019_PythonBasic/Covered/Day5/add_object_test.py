# -*- coding: utf-8 -*- 
from add_object import AddObject

# main function
def main():
    test1 = AddObject("Hello",' ', "Cool")
    test2 = AddObject(' ', "World")
    print(test1 + test2)

    return
if __name__ == "__main__":
    main()