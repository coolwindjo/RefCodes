#일급함수(first class function)
# 할당, 리턴, 인자,
# 함수안에 함수정의(데코레이터..)
def fn():
    print('fn call')

def afn( aa):
    aa()

def rfn():
    return fn

rst = rfn()
rst()
# afn( fn )
# my = fn #shallow copy
# fn() # function call
# my()


