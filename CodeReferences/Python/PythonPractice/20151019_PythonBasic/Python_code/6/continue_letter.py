continue_letter = input("건너뛸 문자를 입력하시오: ")

for letter in "python":
    if letter == continue_letter:
        continue
    print(letter)
