def circle_area_circumference(radius, pi):
    area = pi * (radius ** 2)
    circumference = 2 * pi * radius
    return area, circumference

if __name__ == "__main__":
    result = circle_area_circumference(3, 3.14)
    print("반지름:", 3, "면적과 둘레:", result)
    
    res1, res2 = circle_area_circumference(3, 3.14)
    print("반지름:", 3, "면적:", res1, "둘레:", res2)
