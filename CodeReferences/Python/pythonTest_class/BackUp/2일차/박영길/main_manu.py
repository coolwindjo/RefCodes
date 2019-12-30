import sys
# import copy
# import math
# import statistics

student_list = []

class Student():
    def __init__(self,name, lang_score, eng_score, math_score):
        self.name        = name
        self.lang_score  = lang_score
        self.eng_score   = eng_score
        self.math_score  = math_score


def input_func():
    CTRL = True

    while (True) :

        name     =input('이름:')
        # print(name)
        lang_score     =int(input('국어:'))
        # print(lang_score)
        eng_score      =int(input('영어:'))
        # print(eng_score)
        math_score =int(input('수학:'))
        # print(math_score)
        # stu_mamber = Student(name,lang_score,eng_score, math_score)
        stu_member = Student(name, lang_score, eng_score, math_score)
        # print(stu_member)
        student_list.append(stu_member)
        str_info = '계속 입력하시겠습니까(y/n)\n 입력이 종료 되면 메인메뉴로'
        ctrl_chk = input ('계속 입력하시겠습니까(y/n)\n 입력이 종료 되면 메인메뉴로:')
        # print('-----ctrl_chk', ctrl_chk)

        if ctrl_chk == 'y' :
            # print('계속 입력 중임.')
            # for item in  student_list :
            #     print (item.name, item.eng_score, item.math_score)
            CTRL = True
        else :
            CTRL = False
            break

    # return copy.deepcopy(student_list)
    # sys.exit()




def output_func() :
    # print('output_func')
    print ('------------------------------------------------------------------')
    print ('    이름        국어       영어        수학       총점        평균')
    print ('------------------------------------------------------------------')
    lang_score_total = 0
    eng_score_total = 0
    math_score_total = 0

    lang_score_list = []
    eng_score_list =[]
    math_score_list = []

    student_num  = 0
    for i in  student_list :
        sum_num = i.lang_score + i.eng_score + i .math_score
        mean_num = sum_num / 3.0
        print ('%10s  %10d %10d %10d %10d %10.04f' %(i.name, i.lang_score, i.eng_score,  i.math_score, sum_num ,  mean_num ))
        lang_score_total += i.lang_score
        eng_score_total += i.eng_score
        math_score_total += i.math_score
        lang_score_list.append(i.lang_score)
        eng_score_list.append(i.eng_score)
        math_score_list.append(i.math_score)
        student_num += 1


    max_lang = max(*lang_score_list)
    max_eng  = max(*eng_score_list)
    max_math = max(*math_score_list)

    # student_num  = len(max_lang) + 1
    # print('check studentnum' ,student_num)
    print ('-----------------------------------------------')
    print('종점    : 국어 %10d  영어 %10d  수학 %10d' %(lang_score_total, eng_score_total, math_score_total ))
    print('평균    : 국어 %10.04f  영어 %10.04f  수학 %10.04f' %(lang_score_total/student_num, eng_score_total/student_num, math_score_total/student_num ))


    print('최고점수: 국어 %10d  영어 %10d  수학 %10d' %(max_lang, max_eng, max_math ))


def search_func() :
    # print('search_func')
    name     =input('검색할 이름을 입력하세요 이름 :')

    ctrl_num = 0

    for i in student_list :
        # print (i.name )
        if i.name == name.strip() :

            print ('-----------------------------------------------')
            print ('        이름      국어     영어      수학   ')
            print ('-----------------------------------------------')

            # print (i.name, i.lang_score, i.eng_score,  i.math_score )
            print('%10s  %10d %10d  %10d' %(i.name, i.lang_score, i.eng_score,  i.math_score ))
            ctrl_num = 1
    # for i in student_list :
    if ctrl_num == 0 :
        print ('이 학생은 존재하지 않습니다.')



def exit_func() :
    print('exit_func')
    sys.exit()

def manu() :
    CTRL_LOOP = True


    manu_func ={1: input_func, 2: output_func, 3: search_func, 4 : exit_func }

    manu_display ="""
    메인 메뉴)
     1.입력
     2.출력
     3.검색
     4.종료
     번호를 입력하세요:
     """
    # print(manu_display)

    # student_list = []
    while (CTRL_LOOP) :
        print(manu_display)
        main_selection =int(input('번호:'))
        print(main_selection)
        manu_func[main_selection]()



if __name__ == '__main__' :
    manu()
