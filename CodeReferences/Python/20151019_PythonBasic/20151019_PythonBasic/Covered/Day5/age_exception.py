class AgeException(Exception):
    def __init__(self, msg):
        self._message = msg

def input_age():

    try:
        age = int(input("Enter your age: "))
    except:
        print("Input a valid value.")
        return

    if age < 0:
        raise AgeException("나이는 음수가 될수 없습니다.")
    elif age > 150:
        raise AgeException("150세이상 살수 있을까요?")
    else:
        return age

if __name__ == "__main__":

    try:
        age = input_age()
    except AgeException as e:
        print(e.args[0])
    else:
        print("나이는 %d세입니다." % age)
    

