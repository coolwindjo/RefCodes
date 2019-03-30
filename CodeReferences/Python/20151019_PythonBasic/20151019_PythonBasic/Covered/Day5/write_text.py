import codecs

if __name__ == "__main__":
    fp = codecs.open("text.txt", "w+", "UTF-8")
    fp.write("%d\n" % 1)
    fp.write("%.2f\n" % 3.14)
    fp.write("Hello World\n")
    fp.write("강릉원주대학교 정보기술공학과")
    fp.close()
