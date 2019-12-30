class Car:
    def __init__(self):
        self._speed = 0

    def get_speed(self):
        return self._speed

    def start(self):
        self._speed = 20
    
    def accelerate(self):
        self._speed = self._speed + 30
    
    def stop(self):
        self._speed = 0
    
if __name__ == "__main__":
    my_car1 = Car( )
    my_car2 = Car( )                    
    my_car1.start( )
    my_car2.start( )                     
    my_car1.accelerate( )
    my_car2.accelerate( )
    my_car2.accelerate( )                 
    print("첫번째 자동차 속도:", my_car1.get_speed( )) # 50
    print("두번째 자동차 속도:", my_car2.get_speed( )) # 80
    my_car1.stop( )                     
    my_car2.stop( )
