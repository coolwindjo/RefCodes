class SportCar(object):
    def __init__(self):
        self._speed = 0

    def get_speed(self):
        return self._speed

    def start(self):
        self._speed = 20

    def accelerate(self):
        self._speed = self._speed + 40

    def turbocharge(self):
        self._speed = self._speed + 70

    def stop(self):
        self._speed = 0

if __name__ == "__main__":
    my_sportcar = SportCar()
    my_sportcar.start()
    print("속도:", my_sportcar.get_speed())
    my_sportcar.accelerate()
    print("속도:", my_sportcar.get_speed())
    my_sportcar.turbocharge()
    print("속도:", my_sportcar.get_speed())
    my_sportcar.stop()
