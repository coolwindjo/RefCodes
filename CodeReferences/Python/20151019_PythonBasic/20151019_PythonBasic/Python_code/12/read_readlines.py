if __name__ == "__main__":
    fp = open("text.txt", "rt")
    lines = fp.readlines()
    print(lines)
    fp.close()
