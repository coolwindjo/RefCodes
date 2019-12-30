import extest
from ctypes import *

class Test( Structure):
    _fields_ = [('a',c_int), ('b',c_int),('c',c_char_p)]

tt = Test( 10,20, b'abc')
rst = extest.sfn( addressof(tt) )
print( rst )
print(tt.a, tt.b ,tt.c)
