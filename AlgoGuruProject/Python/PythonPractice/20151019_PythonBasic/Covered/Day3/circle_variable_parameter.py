def circle_area(pi, *radiuses):
    areas = []
    for radius in radiuses:
        area = pi * (radius ** 2)
        areas.append(area)
    return areas

if __name__ == "__main__":
    print(circle_area(3.14, 3, 4, 5))
    print(circle_area(3.14, 6, 7))
