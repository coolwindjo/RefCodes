import codecs

if __name__ == "__main__":
    
    with codecs.open("text.txt", "r", "UTF-8") as fp:
        lines = fp.readlines()

        for line in lines:
            print(line.strip())

    print("Done!")
