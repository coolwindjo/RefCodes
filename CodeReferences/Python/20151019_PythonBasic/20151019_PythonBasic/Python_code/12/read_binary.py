import struct

if __name__ == "__main__":
    intsize = struct.calcsize('i')
    floatsize = struct.calcsize('f')
    
    fp = open('binary.dat', 'rb')
    data = fp.read(intsize)
    num = struct.unpack('i', data)
    print(num)

    data = fp.read(floatsize)
    num = struct.unpack('f', data)
    print(num)

    fp.close()
