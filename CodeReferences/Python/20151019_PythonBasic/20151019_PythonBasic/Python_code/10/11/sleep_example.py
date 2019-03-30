import time

if __name__ == "__main__":
    input("Enter a number:")
    t1 = time.time( )
    time.sleep(3)
    
    input("Enter a number again:")
    t2 = time.time( )
    
    time_gap = t2 - t1

    print("Time gap:", time_gap)

