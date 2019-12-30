# scoping_rule2 global 영역
pi = 3.1415

def circle_area_with_pi(r):
    # circle_area_with_pi의 local 영역
    pi = 3.14
    result = pi * (r ** 2)
    return result

def circle_area_without_pi(r):
    # circle_area_without_pi의 local 영역
    result = pi * (r ** 2)
    return result

def sum_areas():
    results = [circle_area_with_pi(3), circle_area_without_pi(3)]
    return sum(results)       # built-in의 sum 함수를 호출

if __name__ == "__main__":
    print("PI:", pi)
    print("반지름:", 3, "면적:", circle_area_with_pi(3))
    print("반지름:", 3, "면적:", circle_area_without_pi(3))
    print(sum_areas())
