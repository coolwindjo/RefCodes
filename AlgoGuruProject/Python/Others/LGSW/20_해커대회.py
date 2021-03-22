A = list(input().strip())
C = input().strip()
B = []
for c in C:
	if c=="L":
		if A: B.append(A.pop())
	elif c=="R":
		if B: A.append(B.pop())
	elif c=="B":
		if A: A.pop()
	else: A.append(c)
while B: A.append(B.pop())
print("".join(A))
