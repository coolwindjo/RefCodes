g = 10
def fn():
    global g
    g = 100

fn()
print("g=", g)
