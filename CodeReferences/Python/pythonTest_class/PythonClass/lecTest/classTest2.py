class Test:
    def __init__(self, x, y): #생성자(객체생성완료후 자동호출)
        print('const call')
        self.a = x
        self.b = y
    def __del__(self): #객체소멸직전 자동호출
        print("dest call")
    def setData(self,x,y):
        self.a = x
        self.b = y
    def show(self):
        print(self.a, self.b)

def fn():
    obj = Test(11,22)
    obj.show()
    return obj

rst = fn()
print('hello')
rst.show()

# obj = Test(10,20) # obj.__init__(obj, 10,20)
# obj1 = obj
# obj.show()
# obj = 'abc'
# print('hello')







