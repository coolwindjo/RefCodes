# -*- coding: utf-8 -*- 
class AddObject(object):
    """Test Class for add special method."""
    def __init__(self, *kwargs):
        self._str_input = ""
        for item in kwargs:
            if isinstance(item, str):
                self._str_input += item
            else:
                pass
        return super().__init__()

    def __add__(self, obj):
        if type(self) == type(obj) :
            return self.str_input + obj.str_input
        else:
            print("Error occurred!")
            return

    @property
    def str_input(self):
        return self._str_input

# main function
def main():
    return
if __name__ == "__main__":
    main()