import keyword

def is_valid_identifier(ident):
    # Remove leading/trailing whitespace
    ident = ident.strip()
    
    # Check if empty
    if not ident:
        return "Invalid (empty)"
    
    # Check if it starts with a letter or underscore
    if not (ident[0].isalpha() or ident[0] == '_'):
        return "Invalid (must start with letter or underscore)"
    
    # Check if all remaining characters are alphanumeric or underscore
    if not all(c.isalnum() or c == '_' for c in ident[1:]):
        return "Invalid (contains invalid characters)"
    
    # Check if it's a reserved keyword
    if ident in keyword.kwlist:
        return "Invalid (reserved keyword)"
    
    return "Valid"

# Display description once at the top
print("""Description: This is a python program to test whether a given identifier is valid according to common programming language rules (e.g., Python-like identifiers). \n
A valid identifier typically: \n
- Starts with a letter (a-z, A-Z) or underscore (_). \n
- Can be followed by letters, digits (0-9), or underscores. \n
- Cannot be a reserved keyword.""")

# Dynamic input with while True loop
print("Enter an identifier to test (type 'exit' to quit):")
while True:
    user_input = input("Identifier: ").strip()
    if user_input.lower() == 'exit':
        break
    if not user_input:
        print("Please enter an identifier!")
        continue
    
    # Validate and display result
    result = is_valid_identifier(user_input)
    # Display results in tabular format
    print("\nIdentifier     | Result")
    print("---------------|--------------------")
    print(f"{user_input[:15]:<15} | {result}")
    print()