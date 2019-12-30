
class MyIter:
    def __init__(self):
        self.nCnt =0
    def __iter__(self): #for 를 위해..
        print('iter call')
        return self
    def __next__(self):
        print("next call")
        self.nCnt +=1
        if self.nCnt==4:
            raise StopIteration()
        return self.nCnt

it = MyIter()
for n in it:
    print(n)
# print( next(it) ) #it.__next__()
# print( next(it) ) #it.__next__()
# print( next(it) ) #it.__next__()
# print( next(it) ) #it.__next__()




