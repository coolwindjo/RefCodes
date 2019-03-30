def circle_area(radius):
    area = 3.14 * (radius ** 2)
    return area

if __name__ == "__main__":
    print("반지름: %d, 면적: %.2f" % (3, circle_area(3)))
    print("반지름: %d, 면적: %.2f" % (4, circle_area(4)))
    
