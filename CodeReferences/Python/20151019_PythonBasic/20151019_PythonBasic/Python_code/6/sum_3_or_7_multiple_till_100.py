total = 0

for item in range(1, 101):
    if (item % 3) == 0 or (item % 7) == 0:
        total = total + item

print("1부터 100까지에서 3 혹은 7의 배수의 합은", total, "입니다.")
