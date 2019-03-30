def divide(m, n):
    try:
        result = m / n
    except ZeroDivisionError:
        print("0으로 나눌 수 없습니다.")
    except:
        print("ZeroDisionError 이외의 예외가 발생했습니다.")
    else:
        return result
    finally:
        print("나눗셈 연산입니다.")

if __name__ == "__main__":
    result = divide(3, 2)
    print(result)
    print()
    result = divide(3, 0)
    print(result)
    print()
    result = divide(None, 2)
    print(result)
