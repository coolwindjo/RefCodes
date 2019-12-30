def circle_area(radius, pi=3.14):
    area = pi * (radius ** 2)
    return area

if __name__ == "__main__":
    print("면적: %.2f" % circle_area(3))
    print("면적: %.4f" % circle_area(3, 3.1415))
