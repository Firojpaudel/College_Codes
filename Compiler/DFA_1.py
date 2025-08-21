def dfa_ends_with_ab(input_string):
    state = 0  # Initial state
    for char in input_string:
        if state == 0 and char == 'a':
            state = 1
        elif state == 1 and char == 'b':
            state = 2
        elif state == 1 and char == 'a':
            state = 1
        elif state == 2 and char == 'a':
            state = 1
        elif state == 2 and char == 'b':
            state = 2
        else:
            state = 0
    return "Accepted" if state == 2 else "Rejected"

print("Enter strings to test (type 'done' to finish):")
test_strings = []
while True:
    user_input = input("Enter a string: ")
    if user_input.lower() == 'done':
        break
    test_strings.append(user_input)
 
results = [(s, dfa_ends_with_ab(s)) for s in test_strings]

print("\nInput String | Result")
print("-------------|--------")
for s, r in results:
    print(f"{s:12} | {r}")