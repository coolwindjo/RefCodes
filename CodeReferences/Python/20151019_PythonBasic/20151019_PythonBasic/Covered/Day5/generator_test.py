# -*- coding: utf-8 -*- 
def gen_test(data):
    for char in data:
        yield char

def reverse(str_input):
    for i in range(1, len(str_input)+1):
        yield str_input[-i]


# main function
def main():
    gen_iter = iter(gen_test("Hello"))

    for char in gen_iter:
        print(char, end = '')

    print()

    for char in reverse("Hello"):
        print(char, end = '')

    print()

    return
if __name__ == "__main__":
    main()