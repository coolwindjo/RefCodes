def circle_area(radius, print_format):
    pi = 3.14
    area = pi* int(radius) ** 2
    return print_format(area)

def precise_low(value):
    return print("Area: %f" %round(value, 1))

def precise_high(value):
    return print("Area: %f" %round(value, 2))

if __name__ == "__main__":
    circle_area(3, precise_high)
    circle_area(3, precise_low)
