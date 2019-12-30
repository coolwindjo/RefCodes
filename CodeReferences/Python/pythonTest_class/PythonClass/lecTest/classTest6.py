# class Pet(object):
class Pet:
    def Sleep(self):
        print('zzzz')
    def Eat(self):
        print('????')

class Dog(Pet):
    def Speak(self):
        print('bow wow')
    def Eat(self): #overriding
        print('bone')

dog = Dog()
dog.Sleep()
dog.Eat()
dog.Speak()
