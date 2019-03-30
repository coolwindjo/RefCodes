import random


def get_lotto_numbers():
    lotto_numbers = []

    while True:
        if len(lotto_numbers) == 6:
            break

        number = random.randint(1, 45)

        if number in lotto_numbers:
            continue
        else:
            lotto_numbers.append(number)

    return sorted(lotto_numbers)


if __name__ == "__main__":
    lotto_numbers = get_lotto_numbers()
    print(lotto_numbers)
