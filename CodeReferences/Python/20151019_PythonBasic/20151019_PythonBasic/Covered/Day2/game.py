import random
game = ("Scissors", "Rock", "Paper")
desc = """Try to beat the computer!
    0 : Scissors
    1 : Rock
    2 : Paper
    3 : Exit
    >>>"""

while True:
    com = random.randint(0,2)
    try:
        user = int(input(desc))
    except:
        print("Enter a valid value!\n")
        continue

    if user == 3:
        print("Goodbye!")
        break
    elif user < 0 or user > 3:
        print("Enter a valid value!\n")
        continue
    else:
        if (user==com) :
            print("Draw.")
        elif (user==0 and com==1) or (user==1 and com==2) or (user==2 and com==0):
            print("You lose.")
        elif (user==0 and com==2) or (user==1 and com==0) or (user==2 and com==1):
            print("You win.")
        print("User: %s, Computer: %s" % (game[user], game[com]))

    str_user = str(input("Stop => x\n"))
    if str_user == "x" or str_user == "X":
        break
    else:
        continue
