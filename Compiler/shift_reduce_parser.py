# Grammar
print("GRAMMAR is -\nE -> 2E2\nE -> 3E3\nE -> 4\n")

# Take input from user
input_string = input("Enter input string: ").strip()
a = list(input_string)  # input as list
stk = []  # stack
act = ""  # action

print("\n{:<15} {:<20} {:<15}".format("STACK", "INPUT", "ACTION"))

def check():
    """
    Check for reducible patterns in the stack:
    E -> 4, E -> 2E2, E -> 3E3
    """
    global stk
    reduced = False

    # E -> 4
    for z in range(len(stk)):
        if stk[z] == '4':
            stk[z] = 'E'
            print("{:<15} {:<20} {:<15}".format(''.join(stk), ''.join(a), "REDUCE E->4"))
            reduced = True

    # E -> 2E2
    z = 0
    while z < len(stk) - 2:
        if stk[z] == '2' and stk[z + 1] == 'E' and stk[z + 2] == '2':
            stk[z] = 'E'
            del stk[z + 1:z + 3]
            print("{:<15} {:<20} {:<15}".format(''.join(stk), ''.join(a), "REDUCE E->2E2"))
            reduced = True
            z = -1  # restart scanning
        z += 1

    # E -> 3E3
    z = 0
    while z < len(stk) - 2:
        if stk[z] == '3' and stk[z + 1] == 'E' and stk[z + 2] == '3':
            stk[z] = 'E'
            del stk[z + 1:z + 3]
            print("{:<15} {:<20} {:<15}".format(''.join(stk), ''.join(a), "REDUCE E->3E3"))
            reduced = True
            z = -1  # restart scanning
        z += 1

    return reduced

# Append $ only for printing
a.append('$')

# Shift-reduce parsing
i = 0
while i < len(a) - 1:  # do not shift the $ symbol
    stk.append(a[i])
    act = "SHIFT"
    print("{:<15} {:<20} {:<15}".format(''.join(stk), ''.join(a[i:] + a[i+1:]), act))
    while check():  # keep reducing until no more reduction possible
        pass
    i += 1

# Final reduction check
while check():
    pass

# Acceptance check
if stk == ['E', '$'] or stk == ['E']:
    print("\nAccept ✅")
else:
    print("\nReject ❌")
