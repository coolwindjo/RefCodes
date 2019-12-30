class Test:
    def __init__(self, x, y):
        self.a = x
        self.b = y
        self.myDic ={}
    def setData(self,x,y):
        self.a = x
        self.b = y
    def show(self):
        print(self.a, self.b)
    def __repr__(self):
        return "a=%d b=%d"%(self.a,self.b)
    def __setitem__(self, key, value):
        print("call")
        self.myDic[key] = value
    def __getitem__(self, item):
        return self.myDic[item]

obj = Test(11,22)
print( obj ) #obj.__repr__()
obj['aa'] = 10 #obj.__setitem__('aa',10)
obj['bb'] = 20 #obj.__setitem__('bb',20)

print( obj['aa'] )#obj.__getitem__('aa')











