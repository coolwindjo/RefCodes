from vehicle import *

if __name__ == "__main__":
    my_car = Car( )
    my_car.start( )
    my_car.accelerate( )
    speed_mile = change_km_to_mile(my_car.get_speed( ))
    print("속도:", speed_mile, "mile")
    my_car.stop( )
