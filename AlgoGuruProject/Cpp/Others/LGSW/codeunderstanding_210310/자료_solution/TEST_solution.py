import sys

def input_data():
    readl = sys.stdin.readline
    N = int(readl())
    A = list(map(int, readl().split()))    
    return N, A


def get_solution():
    index = 0
    sol = [0 for _ in range(len(A))]
    for num in A:
        while sol[index] != 0:
            index = (index + 1) % N
        sol[index] = num
        index = (index + num) % N
    return sol


sol = []

# 입력받는 부분
N, A = input_data()

# 여기서부터 작성
sol = get_solution()

# 출력하는 부분
print(N)
print(*sol)
