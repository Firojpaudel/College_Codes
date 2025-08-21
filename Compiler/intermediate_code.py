# ====== Helper Classes ======
class TACGenerator:
    def __init__(self):
        self.temp_count = 0
        self.code = []

    def new_temp(self):
        self.temp_count += 1
        return f"t{self.temp_count}"

    def generate(self, expr):
        tokens = self.tokenize(expr)
        postfix = self.infix_to_postfix(tokens)
        result = self.postfix_to_TAC(postfix)
        return result

    def tokenize(self, expr):
        tokens = []
        i = 0
        while i < len(expr):
            if expr[i].isspace():
                i += 1
            elif expr[i].isalnum():
                j = i
                while j < len(expr) and expr[j].isalnum():
                    j += 1
                tokens.append(expr[i:j])
                i = j
            elif expr[i] in "+-*/()=":
                tokens.append(expr[i])
                i += 1
            else:
                raise ValueError(f"Unknown character {expr[i]}")
        return tokens

    def infix_to_postfix(self, tokens):
        precedence = {'=': 0, '+': 1, '-': 1, '*': 2, '/': 2}
        stack = []
        output = []

        for token in tokens:
            if token.isalnum():
                output.append(token)
            elif token == '(':
                stack.append(token)
            elif token == ')':
                while stack and stack[-1] != '(':
                    output.append(stack.pop())
                stack.pop()  # pop '('
            else:  # operator
                while stack and stack[-1] != '(' and precedence.get(stack[-1],0) >= precedence[token]:
                    output.append(stack.pop())
                stack.append(token)
        while stack:
            output.append(stack.pop())
        return output

    def postfix_to_TAC(self, postfix):
        stack = []
        for token in postfix:
            if token.isalnum():
                stack.append(token)
            elif token == '=':
                rhs = stack.pop()
                lhs = stack.pop()
                self.code.append(f"{lhs} = {rhs}")
                stack.append(lhs)
            else:  # operator
                rhs = stack.pop()
                lhs = stack.pop()
                temp = self.new_temp()
                self.code.append(f"{temp} = {lhs} {token} {rhs}")
                stack.append(temp)
        return stack[0]

    def print_code(self):
        print("\nIntermediate Code (Three Address Code):")
        for line in self.code:
            print(line)



if __name__ == "__main__":
    expr = input("Enter arithmetic expression: ")
    tac = TACGenerator()
    tac.generate(expr)
    tac.print_code()
