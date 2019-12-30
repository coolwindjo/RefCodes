import numpy as np

# axis의 개념이 어려워서 만든 예제
#1st의 행렬은 (4, 3) 행렬임
# axis=0일 경우 (4, 3)중에서 4에 해당하는 데이터들을 합하여 (0, 3) -> [3]으로 만듦
# axis=1일 경우 (4, 3)중에서 3에 해당하는 데이터들을 합하여 (4, 0) -> [4]으로 만듦
# 해당하는 축의 차원을 제거한다고 생각하는 것이 편함
# 차원을 줄이는 방법이 sum이나 tf.argmax와 같은 것들 뿐임

lst = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9],
    [1, 2, 3]
]
arr = np.array(lst)
s0 = np.sum(arr, axis=0)
s1 = np.sum(arr, axis=1)
print(s0)
print(s1)

second = [[1, 2, 3]]

arr2 = np.array(second)
s0 = np.sum(arr2, axis=0)
s1 = np.sum(arr2, axis=1)
print(s0)
print(s1)
