class repo:
    def __init__(self):
        self.myDic = {}
    def prints(self):
        print('-----------------------------------------------------------------')
        print('    이름        국어        영어	수학	총점	평균')
        print('----------------------------------------------------------------')
        print(self.myDic)
        print('----------------------------------------------------------------')
    def __setitem__(self, key, value):
        self.myDic[key] = value
    def __getitem__(self, item):
        return (self.myDic[item])

a = 0
b = 0
c = []
d = 0
e = repo()
while int(a) < 4:
    c = []
    print('이름:')
    d = input()
    print('국어:')
    c.append(input())
    print('영어:')
    c.append(input())
    print('수학:')
    c.append(input())
    print(c)
    e[d] = c
    e.prints()
    print('계속 입력하시겠습니까(y/n)?')
    b = input()
    if b == 'n':
        break

