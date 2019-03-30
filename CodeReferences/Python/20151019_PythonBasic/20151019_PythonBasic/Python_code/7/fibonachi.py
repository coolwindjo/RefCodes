def fibo(n):
    if n == 1:
        return 1
    elif n == 2:
        return 1
    else:
        return fibo(n-2) + fibo(n-1)  # 재귀적 호출이 일어나는 부분

if __name__ == "__main__":
    print("10번째 피보나치 수열값: %d" % fibo(10))
    print("20번째 피보나치 수열값: %d" % fibo(20))
    print("30번째 피보나치 수열값: %d" % fibo(30))
    print("35번째 피보나치 수열값: %d" % fibo(35))

