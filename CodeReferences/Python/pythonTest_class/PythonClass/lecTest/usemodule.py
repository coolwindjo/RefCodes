import sys
import mymodule # py , pyc, pyd(c함수)
print( sys.path ) #python path..
sys.path.append( r'd:\my' )
# python -m py_compile mymodule.py => mymodule.pyc
rst = mymodule.hap(10,20)
print(rst)
rst = mymodule.gop(10,20)
print(rst)
