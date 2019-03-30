# -*- coding: utf-8 -*- 
class ParentOne:
    def func(self):
        print("Parent One Func")

class ParentTwo:
    def func(self):
        print("Parent Two Func")

class ChildOne(ParentOne, ParentTwo):
    def child_func(self):
        ParentOne.func(self)
        ParentTwo.func(self)

class ChildTwo(ParentTwo, ParentOne):
    def child_func(self):
        ParentOne.func(self)
        ParentTwo.func(self)

def main():
    child1 = ChildOne()
    child2 = ChildTwo()
    print("\nChild1:")
    child1.child_func()
    child1.func()
    print("\nChild2:")
    child2.child_func()
    child2.func()
    return

if __name__ == "__main__":
    main()