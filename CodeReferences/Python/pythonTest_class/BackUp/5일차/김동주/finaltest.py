from myFunctions import *


def main():
    call = {1: entireLog, 2: visitNum, 3: viewNum, 4: tranSize, 5: mostVisIp, 6: mostVisIpTop5, 7: saveExcel }
    while True:
        s = printMenu()
        print(s)
        call.get(s, exit)()


if __name__ == '__main__':
    main()
