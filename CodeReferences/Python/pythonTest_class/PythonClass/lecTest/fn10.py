#파이썬 switch..
def afn():
    print('afn call')

def bfn():
    print('bfn call')

def defaultFn():
    print("defalult")
menu = {1:afn, 2:bfn}
menu.get( 3, defaultFn )()
# menu[2]()
