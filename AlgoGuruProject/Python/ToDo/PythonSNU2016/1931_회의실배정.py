#-*- coding: utf-8 -*-
## @package Meeting time allocation

def GetNumValue():

    import sys
    try:
        n = int(input())
    except:
        print("[Error] Unexpected error", sys.exc_info()[0])

    return n

def GetNumList(nNum):

    import sys
    naNumList = []
    if nNum == 1:
        naNumList = [int(item) for item in input().split()]
    else:
        for _ in range(nNum):
            try:
                num_set = [int(item) for item in input().split()]
            except:
                print("[Error] Unexpected error.", sys.exc_info()[0])
            naNumList.append(num_set)

    return naNumList
    
def MeetingAllocation(nTotalNumOfMeetings, naMeetingList):
    
    for i in range(nTotalNumOfMeetings):
        print(naMeetingList[i])

    naMeetingList.sort()
    
    for i in range(nTotalNumOfMeetings):
        print(naMeetingList[i])

    naMeetingsAtTheSameTime = []
    naMeetingsAtTheSameTime.append(naMeetingList[0])
    for i in range(1, nTotalNumOfMeetings):
        if (naMeetingList[i-1][0] == naMeetingList[i][0]):
            naMeetingsAtTheSameTime.append(naMeetingList[i])
        else:
            naMeetingsAtTheSameTime.sort(1)
    
    
    return nNumOfMeetings


def main():
    
    n = GetNumValue()
    naNumList = GetNumList(n)
    nNumOfMeetings = MeetingAllocation(n, naNumList)
    print(nNumOfMeetings)

    return

if __name__ == "__main__":
    main()