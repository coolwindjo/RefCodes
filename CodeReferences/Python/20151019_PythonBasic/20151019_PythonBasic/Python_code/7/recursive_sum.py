def sum(n):
    if n == 1:
        return 1
    else:
        return sum(n-1) + n       # 재귀적 호출이 일어나는 부분

if __name__ == "__main__":
    print("1부터 100까지 합: %d" % sum(100))
    print("1부터 200까지 합: %d" % sum(200))
