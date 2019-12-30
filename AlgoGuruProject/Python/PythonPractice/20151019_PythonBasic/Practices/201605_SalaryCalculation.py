# -*- coding: utf-8 -*-
import sys

if __name__ == '__main__':

    num_list = []
    try:
        with open('input_file.txt', 'r') as f:
            for line in f.readlines():
                num_list.append(line.strip())
    except IOError as e:
        print ("I/O error({0}): {1}".format(e.errno, e.strerror))
    except ValueError:
        print ("Could not convert data to an integer.")
    except:
        print ("Unexpected error:", sys.exc_info()[0])
        raise

    f.close()

    for i in range(10):
        try:
            nInput = int(input("input time: "))
            if int(nInput) < 0:
                break;
            else:
                num_list.append(nInput)
        except ValueError:
            continue

        nPayList = []
        i = 0
        for sz_num in num_list:
            num = int(sz_num)
            if num <= 40:
                nPay = num * 3
            else:
                nPay = 40*3 + (num-40) * 4.5
            nPayList.append(nPay)

        #strOutput = "Input: " + num_list[0]
        
        i = 0
        for nPay in nPayList:
            print ("Input: "),
            print (num_list[i]),
            print (", output: "),
            print (nPay)
            i += 1
  
            
