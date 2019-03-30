if __name__ == "__main__":
    fp = open("hello.txt", "rt")
    contents = fp.read()
    print(contents)
    fp.close()
