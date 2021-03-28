print('Hello', 'World', sep=' -> ')
print('Hello world', end='  ^^*')
print('     Hello world')

fp = open("hello.txt", 'wt')
print('Hello world', file = fp)