#동일한 클래스에서 여러개의 객체가 발생한경우
#멤버데이터는 메모리별도로
#멤버함수(코드) 는 공유
#어떻게 각각의 멤버데이터 영역에 R/w self

class Test:
    def __init__(self): #생성자
        self.a = 10
        self.b = 20
    def setData(self,x,y):
        print('self id:', id(self))
        self.a = x
        self.b = y
    def show(self):
        print('show id', id(self) )
        print(self.a, self.b)

obj = Test() # obj.__init__(obj)
print("obj id:", id(obj) )
obj.setData(1,2) #obj.setData(obj,1,2)
obj.show() #obj.show(obj)

obj1 = Test() # obj1.__init__(obj1)
print("obj1 id:", id(obj1) )
obj1.setData(11,22) #obj1.setData(obj1,11,22)
obj1.show()#obj1.show(obj1)







