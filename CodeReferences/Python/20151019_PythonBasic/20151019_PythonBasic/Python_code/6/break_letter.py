break_letter = input("중단할 문자를 입력하시오: ")

for letter in "python":
    if letter == break_letter:
        break
    print(letter)
else:
    print("모든 문자 출력 완료!")
