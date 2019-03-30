# -*- coding: utf-8 -*- 
def assert_test(arg):
    assert type(arg) == int, "Input value should be an integer."
    return (str(arg)+ ' ') * 10

# main function
def main():
    ret = assert_test(10)
    print(ret)
    #ret = assert_test("arg")

    return
if __name__ == "__main__":
    main()