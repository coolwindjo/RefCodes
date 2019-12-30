def inputMenu(list):

    while True:
        data = dict()
        data['name'] = input('이름:')
        data['ko'] = int(input('국어:'))
        data['en'] = int(input('영어:'))
        data['math'] = int(input('수학:'))
        data['sum'] = data['ko']+data['en']+data['math']
        data['avg'] = data['sum']/3
        list.append(data)
        if(input('계속입력하시겠습니다.(y/n)?') == 'n'):
            break

def outputMenu(list):
    print('ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ')
    print('      이름      국어      영어      수학      총점      평균')
    print('ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ')

    koSum = 0
    enSum = 0
    mathSum = 0
    cnt = len(list)
    for l in list:
        print('  {name}   {ko}   {en}   {math}   {sum}   {avg}'.format(**l))
        koSum += l['ko']
        enSum += l['en']
        mathSum += l['math']
    print('ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ')
    print('총점 : 국어{} 영어{} 수학{}'.format(koSum,enSum,mathSum))
    print('평균 : 국어{} 영어{} 수학{}'.format(koSum/cnt, enSum/cnt, mathSum/cnt))

    print('국어최고점수 : {}영어최고점수 : {}수학최고점수 : {}'.format(mymax(list,lambda v:v['ko'])['ko'],mymax(list,lambda v:v['en'])['en'],mymax(list,lambda v:v['math'])['math']))

def mymax(dt, key):
    mx = None
    for n in dt:
        if mx==None or key(n)>key(mx):
            mx = n
    return mx
def searchMenu(list):
    name = input('검색할 이름을 입력하세요:')
    print('ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ')
    print('      이름      국어      영어      수학      총점      평균')
    print('ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ')
    d = dict()
    for l in list:
        if l['name'] == name:
            print('  {name}   {ko}   {en}   {math}   {sum}   {avg}'.format(**l))
    print('ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ')

