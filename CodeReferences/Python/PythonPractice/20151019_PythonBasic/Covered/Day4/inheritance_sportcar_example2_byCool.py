class Car(object):
    def __init__(self, name):
        self._speed = 0
        self._name = name

    @property
    def speed(self):
        return self._speed

    def get_name(self):
        return self._name
    name = property(get_name)

    def start(self):
        self._speed = 20

    def accelerate(self):
        self._speed = self._speed + 30
        print("Go Go")

    def stop(self):
        self._speed = 0

class SportCar(Car):
    def __init__(self, name, color):
        Car.__init__(self, name)
        self._color = color
               
    '''
    def accelerate(self):
        Car.accelerate(self)
        self._speed = self._speed + 10
        print("Go Go Go!")
        '''

    def accelerate(self, *speed):
        if len(speed) == 0:
            Car.accelerate(self)
        else:
            for item in speed:
                self._speed += item
        print("Go Go Go!")
        return

    def turbocharge(self):
        self._speed = self._speed + 70
   
    @property
    def color(self):
        return self._color

if __name__ == "__main__":
    my_sportcar = SportCar("Avante","Yellow")
    print(my_sportcar.__dict__)
    print("색상:", my_sportcar.color)
    print("Name:", my_sportcar.name)
    my_sportcar.start()
    print("속도:", my_sportcar.speed)
    my_sportcar.accelerate(10,20,30)
    print("속도:", my_sportcar.speed)
    my_sportcar.turbocharge()
    print("속도:", my_sportcar.speed)
    my_sportcar.stop()
