class Radio:
    def __init__(self):
        print("라디오가 생성되었습니다.")
        pass

    def turn_on(self):
        print("라디오를 켭니다.")

    def turn_off(self):
        print("라디오를 끕니다.")

class Car:
    def __init__(self):
        self._speed = 0
        print("자동차가 생성되었습니다.")
        self._radio = Radio( )

    def get_speed(self):
        return self._speed

    def start(self):
        self._speed = 20
        print("자동차가 출발합니다.")

    def accelerate(self):
        self._speed = self._speed + 30
        print("자동차가 가속을 합니다.")

    def stop(self):
        self._speed = 0
        print("자동차가 정지합니다.")

    def turn_on_radio(self):
        self._radio.turn_on( )

    def turn_off_radio(self):
        self._radio.turn_off( )

if __name__ == "__main__":
    my_car = Car( )                    
    my_car.start()                      
    my_car.turn_on_radio( )             # 1
    my_car.accelerate()                 
    my_car.turn_off_radio( )             # 2
    my_car.stop()

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
