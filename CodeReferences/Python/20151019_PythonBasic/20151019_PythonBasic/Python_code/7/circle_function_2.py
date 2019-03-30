def circle_area(radius, pi):
    area = pi * (radius ** 2)
    return area

if __name__ == "__main__":
    print("반지름:", 3, "PI", 3.14, "면적:", circle_area(3, 3.14))
    print("반지름:", 3, "PI", 3.1415, "면적:", circle_area(3, 3.1415))
