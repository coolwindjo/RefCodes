polygon = {"triangle":2, "rectangle": 1, "line": 0}

print("### dict keys")
for key in polygon.keys():
    print(key)

print("### dict values")
for val in polygon.values():
    print(val)

print("### dict items")
for key, val in polygon.items():
    print(key, val)

print ("### dict")
for item in polygon:
    print(item)

print()
