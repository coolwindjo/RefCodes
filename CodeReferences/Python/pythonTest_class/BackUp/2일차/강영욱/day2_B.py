
total = []

def printResult():
    print('-----------------------------')
    print(' 이름     국어     영어     수학')
    print('-----------------------------')
    for n in total:
        print(' {}     {}     {}     {}'.format( *n ))
    print('-----------------------------')


while 1:
    data = []
    data.append(input('이름:'))
    data.append(input('국어:'))
    data.append(input('영어:'))
    data.append(input('수학:'))

    total.append(data)

    r = input('계속 입력하시겠습니까(y/n)?:')
    if r == 'n':
        break

printResult()


