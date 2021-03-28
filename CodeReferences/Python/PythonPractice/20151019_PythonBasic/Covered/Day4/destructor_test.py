class Test:
    def __init__(self, **kwargs):
        print("Test class created!")
        return super().__init__(**kwargs)
    def __del__(self):
        print("Test class deleted!")
        return
    def __delattr__(self, **kwargs):
        return super().__delattr__(**kwargs)

def main():
    test1 = Test()
    import sys
    sys.getrefcount(test1)

    test2 = test1
    sys.getrefcount(test1)

    del test2

    del test1

    '''
    >>> test1 = Test()
    Test class created!
    >>> import sys
    >>> sys.getrefcount(test1)
    2
    >>> test2 = test1
    >>> sys.getrefcount(test1)
    3
    >>> del test2
    >>> sys.getrefcount(test1)
    2
    >>> del test1
    Test class deleted!
    >>> 
    '''
    return

if __name__ == "__main__":
    main()