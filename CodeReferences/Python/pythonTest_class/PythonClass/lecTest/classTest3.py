class Test:
    st = 100 # static 변수
    def __init__(self, x, y):
        self.a = x #인스턴스변스(객체생성필요)
        self.b = y
    def setData(self,x,y):
        self.a = x
        self.b = y
    def show(self): #객체.멤버함수() 인스턴스함수.
        print(self.a, self.b)

    @staticmethod
    def setSt(x): #static method
        Test.st = x
        print('stfn...')

    @classmethod
    def setC(cls,x):
        cls.st = x

Test.setC(200) #Test.setC(Test, 200 )
print( Test.st )

# Test.setSt(90)
# print( Test.st )
# Test.st =110
# print( Test.st )
# obj = Test(11,22)
# obj.show() # obj.show(obj)
# obj1 = Test(110,220)



