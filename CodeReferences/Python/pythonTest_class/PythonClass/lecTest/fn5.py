#파이썬이 제공하는 전역변수
# __name__ = '__main__'
# __doc__ = None
# __file__= 'D:/pythonTest/fn5.py'
g = 10
def fn():
    g = 100
    print( locals() )
fn()
print("============")

# print( "g=", g)
# print( __file__ )
# print( globals() )
