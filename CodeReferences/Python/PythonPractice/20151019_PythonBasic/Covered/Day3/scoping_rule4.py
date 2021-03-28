# scoping_rule3 global 영역
pi = 3.14

def circle_area(r):
    # circle_area_with_pi의 local 영역
    global pi           # 이 공간에서의 pi는 global의 pi임을 선언
    pi = pi + 0.0015
    result = pi * (r ** 2)
    return result

if __name__ == "__main__":
    print("PI:", pi)
    print("반지름:", 3, "면적:", circle_area(3))
    print("PI:", pi)
