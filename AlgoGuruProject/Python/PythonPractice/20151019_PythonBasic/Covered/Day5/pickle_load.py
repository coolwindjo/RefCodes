import pickle

if __name__ == "__main__":
    fp = open("binary.dat", "rb")
    data = pickle.load(fp)
    print(data)
    data = pickle.load(fp)
    print(data)
    data = pickle.load(fp)
    print(data)
    data = pickle.load(fp)
    print(data)
    data = pickle.load(fp)
    print(data)
    data = pickle.load(fp)
    print(data)
    data = pickle.load(fp)
    print(data)
    fp.close()
