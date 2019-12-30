import math

#1. 반지름과 높이를 입력받아 다음을 구하시요
def cylinde_cone(r,h) :
    #print(math.pi)

    #cyclide (원기둥)
    ret_cylinde = math.pi*r*r*h

    # 원뿔 (1/3)*math.pi*r*r*h
    ret_cone    = (1/3)* ret_cylinde
    return ret_cylinde, ret_cone

#2. 하나의 도를 입력받아 화씨값을 구하시요
def C_to_F(c_number) :
    return c_number*1.80000 + 32.00

#3. cm 를 입력받아 인치를 구하시요
def cm_to_inch(cm_number) :
    return float(cm_number) / 2.54

#4. km 를 입력받아 마일을 구하시요
def kilo_to_mile(kilo_number) :
    return float(kilo_number) / 1.609344

#5. 2개의 정수를 입력받아 절대값의 합을 구하시요
def abs_sum(a,b) :
    return abs(a) + abs(b)

#7. 3개의 정수를 입력받아 가장큰값을 구하시요.
def max_num(a,b,c) :
    max_list = []
    if a >= b :
        max_list.append(a)
    else :
        max_list.append(b)

    a_b_num = max_list.pop()
    if c >= a_b_num :
        return c
    else :
        return a_b_num


# 10. 하나의 점수를 읽어 90~100 'A' 80~89 'B' 70~79 'C' 60~69 'D' 나머지 'F'
def score_func(score) :
    ret_score = {10:'A', 9:'A', 8:'B', 7:'C', 6:'D' ,
                 5:'F', 4:'F',3:'F', 2:'F', 1:'F', 0 :'F'}
    ret_key = score //10

    return ret_score[ret_key]



#11. salary=[1000,2000,3000,4000,5000 ] 의 연봉데이터가 있을때 세금 3.3을 제한
#실수령액을 제너레이터를 이용하여 작성하시요
def cal_salary(salary) :
    res =(sal*(1-0.033) for sal in salary)
    return res

if __name__ == '__main__' :
    print('-'*50)
    print('1. 반지름과 높이를 입력받아 다음을 구하시요')
    r = 20
    h = 10
    ret1, ret2 = cylinde_cone(r,h)



    print('%d half redius, %d height -> result 원기둥 %.04f, result 원뿔 %.04f' %(r,h, ret1,ret2))

    print('\n')
    print('-'*50)
    print('2. 하나의 도를 입력받아 화씨값을 구하시요')
    a  = 1.8
    ret = C_to_F(a)
    print('%.04f C -> result %.04f F' %(a, ret))

    print('\n')
    print('-'*50)
    print('3. cm 를 입력받아 인치를 구하시요')
    a  = 1
    ret = cm_to_inch(a)
    print('%.04f cm -> result %.04f inch' %(a, ret))

    print('\n')
    print('-'*50)
    print('4. km 를 입력받아 마일을 구하시요')
    a  = 20
    ret = kilo_to_mile(a)
    print('%.04f km -> result %.04f mile' %(a, ret))


    print('\n')
    print('-'*50)
    print('5. 2개의 정수를 입력받아 절대값의 합을 구하시요')
    a = 5
    b = -10
    ret = abs_sum(a, b)
    print('|%d| + |%d| --> result %d'%(a,b,ret))


    print('\n')
    print('-'*50)
    print('7. 3개의 정수를 입력받아 가장큰값을 구하시요.')
    a = 4
    b = 11
    c = 10
    ret = max_num(a,b,c)
    print('%d, %d, %d --> result max num %d'%(a,b,c, ret))

    a = 69
    ret = score_func(a)

    print('\n')
    print('-'*50)
    print("# 10. 하나의 점수를 읽어 90~100 'A' 80~89 'B' 70~79 'C' 60~69 'D' 나머지 'F")
    print('%d  --> result score %s' %(a, ret))


    salary=[1000,2000,3000,4000,5000 ]
    gen_salary = cal_salary(salary)

    print('11. salary=[1000,2000,3000,4000,5000 ] 의 연봉데이터가 있을때 세금 3.3을 제한')

    #for item in gen_salary :
    #    print(item)
    print('세금 제하기전 salary ---세금 3.3% 제한 salary ')
    for item, item2 in zip(salary, gen_salary) :
        print(item, '--',item2)
