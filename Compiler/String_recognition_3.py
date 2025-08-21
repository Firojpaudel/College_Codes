def recognize_string(input_string):

    input_string = input_string.strip()
    
    # Check a* (zero or more 'a')
    state_a_star = 0
    for char in input_string:
        if char != 'a':
            break
        state_a_star += 1
    if all(c == 'a' for c in input_string) or not input_string:
        result_a_star = "Accepted (a*)"
    else:
        result_a_star = "Rejected (a*)"
    
    # Check a*b+ (zero or more 'a' followed by one or more 'b')
    state_a_b_plus = 0  # 0: start, 1: after 'a'*, 2: after 'b'+
    for char in input_string:
        if state_a_b_plus == 0 and char == 'a':
            state_a_b_plus = 1
        elif state_a_b_plus == 1 and char == 'a':
            continue
        elif state_a_b_plus == 1 and char == 'b':
            state_a_b_plus = 2
        elif state_a_b_plus == 2 and char == 'b':
            continue
        else:
            state_a_b_plus = -1  # Invalid state
            break
    result_a_b_plus = "Accepted (a*b+)" if state_a_b_plus == 2 else "Rejected (a*b+)"
    
    # Check abb (exactly "abb")
    result_abb = "Accepted (abb)" if input_string == "abb" else "Rejected (abb)"
    
    return result_a_star, result_a_b_plus, result_abb


print("Enter a string to recognize (type 'exit' to quit):")
while True:
    user_input = input("String: ").strip()
    if user_input.lower() == 'exit':
        break
    if not user_input:
        print("Please enter a string!")
        continue
    
    # Validate and display results
    result_a_star, result_a_b_plus, result_abb = recognize_string(user_input)

    print("\nString         | a*       | a*b+     | abb")
    print("---------------|----------|----------|--------")
    print(f"{user_input[:15]:<15} | {result_a_star} | {result_a_b_plus} | {result_abb}")
    print()