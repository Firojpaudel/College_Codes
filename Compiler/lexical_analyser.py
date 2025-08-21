import keyword

def lexical_analyzer(code):
    # Define token categories and patterns
    tokens = []
    i = 0
    code = code.strip()
    
    while i < len(code):
        char = code[i]
        
        # Skip whitespace
        if char.isspace():
            i += 1
            continue
        
        # Identifiers and keywords
        if char.isalpha() or char == '_':
            word = char
            i += 1
            while i < len(code) and (code[i].isalnum() or code[i] == '_'):
                word += code[i]
                i += 1
            token_type = "KEYWORD" if word in keyword.kwlist else "IDENTIFIER"
            tokens.append((word, token_type))
            continue
        
        # Operators and delimiters
        if char in "+-*/=<>!&|()[]{},;:":
            if i + 1 < len(code) and char + code[i + 1] in ["==", "!=", "<=", ">=", "&&", "||", "+=", "-="]:
                tokens.append((char + code[i + 1], "OPERATOR"))
                i += 2
            else:
                tokens.append((char, "OPERATOR" if char in "+-*/=<>!&|" else "DELIMITER"))
                i += 1
            continue
        
        # Unknown character
        tokens.append((char, "UNKNOWN"))
        i += 1
    
    return tokens

print(f"{'='*10} Lexical Analyzer in Action {'='*10}")
print("Enter source code for lexical analysis (type 'exit' to quit):")
while True:
    user_input = input("Code: ").strip()
    if user_input.lower() == 'exit':
        break
    if not user_input:
        print("Please enter source code!")
        continue
    
    # Perform lexical analysis and display results
    tokens = lexical_analyzer(user_input)
    # Display results in tabular format
    print("\nToken          | Type")
    print("---------------|----------")
    for token, token_type in tokens:
        print(f"{token:<15} | {token_type}")
    print()