#연산용 클래스 static
#데이터용 클래스 인스턴스..
class Circle:
    @staticmethod
    def circleArea(r):
        return r**2*3.14
    @staticmethod
    def cylinder( r, h):
        return r**2*3.14*h

class Student:
    def __init__(self,name,age):
        self.name = name
        self.age = age
    def show(self):
        print(self.name, self.age)
# print( Circle.circleArea(3))
# print( Circle.cylinder(3,10))

data =[]
data.append( ('이순신',20) )
data.append( ('홍길동',30) )
print(data )
for n in data:
    print( '이름:{} 나이:{}'.format( *n ) )

# data.append( Student('이순신',20) )
# data.append( Student('홍길동',30) )
# # [3000번지,4000번지]
# for dt in data:
#     dt.show()
# data[1].show()














