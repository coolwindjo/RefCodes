pi = 3.14

def circle_area(r):
    global pi
    pi = pi + 0.0015
    area = pi * (int(r) ** 2)
    return area

if __name__ == "__main__":
    radius = input("Enter Radius :")
    print(circle_area(radius))
