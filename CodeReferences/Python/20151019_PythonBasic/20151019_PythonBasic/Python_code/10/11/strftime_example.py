import time

if __name__ == "__main__":
    print("년도:", time.strftime("%Y", time.localtime()))
    print("월:", time.strftime("%m", time.localtime()))
    print("일:", time.strftime("%d", time.localtime()))
    print("요일:", time.strftime("%A", time.localtime()))
