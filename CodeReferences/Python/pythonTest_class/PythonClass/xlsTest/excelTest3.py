import openpyxl
wb = openpyxl.Workbook()
ws = wb.active
while True:
    name = input('이름:')
    kor = int( input('국어:') )
    eng = int( input('영어:') )
    ws.append( (name, kor,eng) )
    yn = input("계속입력(y/n):")
    if yn =='n':
        break
for c1,c2,c3 in ws:
    print( c1.value,c2.value,c3.value, sep='\t')
wb.save('xlsTest/result/my2.xlsx')


