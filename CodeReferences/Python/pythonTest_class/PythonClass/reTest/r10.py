import re
s1 = '''kind apple ki
i banna straw'''
s2 ='''lg hi test ki\ni
hello korea
lg first
python test
lg python
'''

def fn3():
    try:
        match = re.search('AP*LE', s1, re.IGNORECASE )
        print( match.group() )
    except Exception as err:
        print('not found')

def fn2():
    try:
        match = re.search('ki.i', s1, re.DOTALL )
        print( match.group() )
        match = re.search('ki.i', s2, re.DOTALL )
        print( match.group() )
    except Exception as err:
        print('not found')

def fn1():
    try:
        match = re.search('apple', s1)
        print( match.group() )
        print( match.start())
        print( match.end())
        print( match.span())
    except Exception as err:
        print('not found')

try:
    my = re.findall('^lg\s\w+', s2,re.MULTILINE )
    print( my )
    
    fn3()
    fn2()
    fn1()
except Exception as err:
    print('not found')


