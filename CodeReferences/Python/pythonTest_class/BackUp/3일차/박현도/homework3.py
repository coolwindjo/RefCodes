import csv
import openpyxl
from statistics import mean
fp=open('CCTV_in_Seoul.csv',encoding='utf-8')
rd = csv.reader(fp)
wb=openpyxl.Workbook() # excel을 담당하는 객체
wb=openpyxl.load_workbook('cctv.xlsx')
ws=wb.active # 기본으로 생성되는 sheet 참조를 얻는다.
def writeXL():
    cnt=int(0)
    print(rd)
    for n,k,e,a,b,c in rd:
        if cnt==0:
            ws.append((n,k,e,a,b,c ))
        else :
            ws.append((n,int(k),int(e),int(a),int(b),int(c)))
            print(type(int(k)))
        cnt+=1
    fp.close()
    wb.save('cctv.xlsx')


# 1. cctv 소계의 평균을 구하시오.
def average():
     cnt=int(0)
     print(cnt)
     all=int(0)
     for c1,c2,c3,c4,c5,c6 in ws:
         if type(c2.value)==int:
            all+=int(c2.value)
            print(all)
         cnt+=1
      #print(cnt)
     print( 'cctv 소계의 평균 : ',all/25)

def maxnum():
    cnt=int(0)
    temp=int(0)
    for c1,c2,c3,c4,c5,c6 in ws:
        if type(c2.value)==int:
            if temp<c2.value:
                 temp=c2.value
    for c1,c2,c3,c4,c5,c6 in ws:
       if c2.value==temp:
           print("가장 소계가 많은 기관명:%d 소계 %d",c1.value,c2.value)
           break

# def top5():
    
writeXL()
average()
maxnum()
