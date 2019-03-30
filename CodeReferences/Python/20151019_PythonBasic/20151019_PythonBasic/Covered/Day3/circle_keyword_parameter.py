def circle_area(radius, pi):
    area = pi * (radius ** 2)
    return area

if __name__ == "__main__":
    print("반지름:", 3, "면적:", circle_area(3, 3.14))
    print("반지름:", 3, "면적:", circle_area(3, pi = 3.14))
    print("반지름:", 3, "면적:", circle_area(radius = 3, pi = 3.14))
    print("반지름:", 3, "면적:", circle_area(pi = 3.14, radius = 3))
