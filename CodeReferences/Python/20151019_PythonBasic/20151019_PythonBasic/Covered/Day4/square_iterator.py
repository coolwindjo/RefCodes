class Square(object):
    def __init__(self, start, end):
        self._number = start - 1
        self._end = end

    def __iter__(self):
        return self

    def __next__(self):
        if self._number == self._end:
            raise StopIteration
            #pass # Infinite repetition
        else:
            self._number = self._number + 1
            return self._number ** 2

if __name__ == "__main__":
    squares = iter(Square(1, 5))
    for item in squares:
        print(item, end=" ")

    print()

    squares = iter(Square(1,3))
    print(next(squares))
    print(next(squares))
    print(next(squares))
    print(next(squares))

