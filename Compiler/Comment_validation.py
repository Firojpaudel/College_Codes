def validate_python_comment(comment):
    # Removing leading/trailing whitespace
    comment = comment.strip()
    
    # Check for single-line comment (#)
    if comment.startswith('#'):
        return "Valid single-line comment"
    
    # Check for multi-line comment (""" or ''')
    if (comment.startswith('"""') and comment.endswith('"""')) or \
       (comment.startswith("'''") and comment.endswith("'''")):
        content = comment[3:-3].strip() if '"""' in comment else comment[3:-3].strip()
        return "Valid multi-line comment" if content or len(comment) > 6 else "Invalid multi-line comment (empty)"
    
    # Check for standalone string as comment (custom rule)
    if (comment.startswith('"') and comment.endswith('"')) or \
       (comment.startswith("'") and comment.endswith("'")):
        content = comment[1:-1].strip()
        return "Valid string comment" if content else "Invalid string comment (empty)"
    
    return "Invalid comment"


print("Enter a comment to validate (type 'exit' to quit):")
while True:
    user_input = input("Comment: ").strip()
    if user_input.lower() == 'exit':
        break
    if not user_input:
        print("Please enter a comment!")
        continue
    

    result = validate_python_comment(user_input)

    print("\nComment         | Result")
    print("----------------|--------------------")
    print(f"{user_input[:15]:<16} | {result}")
    print()